/*
 * Noob64 - A Nintendo 64 emulator.
 *
 * (c) Copyright 2012 Quentin Metzler and 
 * Romain Richard.
 *
 * Permission to use, copy, modify and distribute Noob64 in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Noob64 is freeware for PERSONAL USE only. Commercial users should
 * seek permission of the copyright holders first. Commercial use includes
 * charging money for Noob64 or software derived from Noob64.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so if they want them.
 *
 */

#include "StdAfx.h"

void n64_cic_nus_6105(char chl[], char rsp[], int len)
{
	static char lut0[0x10] = {
		0x4, 0x7, 0xA, 0x7, 0xE, 0x5, 0xE, 0x1, 
		0xC, 0xF, 0x8, 0xF, 0x6, 0x3, 0x6, 0x9
	};
	static char lut1[0x10] = {
		0x4, 0x1, 0xA, 0x7, 0xE, 0x5, 0xE, 0x1, 
		0xC, 0x9, 0x8, 0x5, 0x6, 0x3, 0xC, 0x9
	};
	char key, *lut;
	int i, sgn, mag, mod;

	for (key = 0xB, lut = lut0, i = 0; i < len; i++) {
		rsp[i] = (key + 5 * chl[i]) & 0xF;
		key = lut[rsp[i]];
		sgn = (rsp[i] >> 3) & 0x1;
		mag = ((sgn == 1) ? ~rsp[i] : rsp[i]) & 0x7;
		mod = (mag % 3 == 1) ? sgn : 1 - sgn;
		if (lut == lut1 && (rsp[i] == 0x1 || rsp[i] == 0x9))
			mod = 1;
		if (lut == lut1 && (rsp[i] == 0xB || rsp[i] == 0xE))
			mod = 0;
		lut = (mod == 1) ? lut1 : lut0;
	}
}

void ProcessControllerCommand ( int Control, BYTE * Command) 
{
	switch (Command[2]) 
	{
	case 0x00: // check
	case 0xFF: // reset & check ?
		if ((Command[1] & 0x80) != 0)
			break;
		//if (Command[0] != 1 || Command[1] != 3)
	//		DebugError("What am I meant to do with this Controller Command");
		
		if (CONTROLLER::controllers[Control].Present) 
		{
			Command[3] = 0x05;
			Command[4] = 0x00;
			switch ( CONTROLLER::controllers[Control].Plugin) 
			{
				case PLUGIN_RUMBLE_PAK: 
					Command[5] = 1; 
					break;
				case PLUGIN_MEMPAK: 
					Command[5] = 1; break;
				case PLUGIN_RAW: 
					Command[5] = 1; 
					break;
				default: 
					Command[5] = 0; 
					break;
			}
		}
		else
		{
			Command[1] |= 0x80;
		}
		break;

	case 0x01: // read controller
		/*if (Command[0] != 1 || Command[1] != 4)
			DebugError("What am I meant to do with this Controller Command");*/
		if (!CONTROLLER::controllers[Control].Present)
			Command[1] |= 0x80;
		break;
	case 0x02: //read from controller pack
		/*if (LogOptions.LogControllerPak) 
			LogControllerPakData("Read: Before Gettting Results");
		if (Command[0] != 3 || Command[1] != 33)
			DebugError("What am I meant to do with this Controller Command");*/
		if (CONTROLLER::controllers[Control].Present)
		{
			DWORD address = ((Command[3] << 8) | Command[4]);
			switch (CONTROLLER::controllers[Control].Plugin) 
			{
				case PLUGIN_RUMBLE_PAK:
					memset(&Command[5], (address >= 0x8000 && address < 0x9000) ? 0x80 : 0x00, 0x20);
				//	Command[0x25] = Mempacks_CalulateCrc(&Command[5]);
					break;
				case PLUGIN_MEMPAK: 
				//	ReadFromMempak(Control, address, &Command[5]); 
					break;
				case PLUGIN_RAW: 
					CONTROLLER::controllerCommand(Control, Command);
					break;
				default:
					memset(&Command[5], 0, 0x20);
					Command[0x25] = 0;
					break;
			}
		} 
		else
		{
			Command[1] |= 0x80;
		}
		break;
	case 0x03: //write controller pak
		/*if (Command[0] != 35 || Command[1] != 1) 
			DebugError("What am I meant to do with this Controller Command");*/
		
		if (CONTROLLER::controllers[Control].Present)
		{
			DWORD address = ((Command[3] << 8) | Command[4]);
			switch (CONTROLLER::controllers[Control].Plugin) 
			{
				case PLUGIN_MEMPAK: 
				//	WriteToMempak(Control, address, &Command[5]); 
					break;
				case PLUGIN_RAW: 
					CONTROLLER::controllerCommand(Control, Command);
					break;
				case PLUGIN_RUMBLE_PAK: 
					CONTROLLER::rumbleCommand(Control, *(BOOL *)(&Command[5]));
					break;
				default:
					//Command[0x25] = Mempacks_CalulateCrc(&Command[5]);
					break;
			}
		} else {
			Command[1] |= 0x80;
		}
		break;
	default:
		;
	}
}

void PIF_RAM::PifRamWrite (void)
{
	int Channel = 0, CurPos = 0;
	char Challenge[30], Response[30];
	Channel = 0;

	if( data.pram[0x3F] > 0x1)
	{ 
		switch (data.pram[0x3F]) 
		{
		case 0x02:
			// format the 'challenge' message into 30 nibbles for X-Scale's CIC code
			for (int i = 0; i < 15; i++)
			{
				Challenge[i*2] =   (data.pram[48+i] >> 4) & 0x0f;
				Challenge[i*2+1] =  data.pram[48+i]       & 0x0f;
			}
			// calculate the proper response for the given challenge (X-Scale's algorithm)
			n64_cic_nus_6105(Challenge, Response, CHL_LEN - 2);
			// re-format the 'response' into a byte stream
			for (int i = 0; i < 15; i++)
			{
				data.pram[48+i] = (Response[i*2] << 4) + Response[i*2+1];
			}
			// the last byte (2 nibbles) is always 0
			data.pram[63] = 0;
			break;
		case 0x08: 
			data.pram[0x3F] = 0; 
		    RCP::getMI()->setIntr(RCP::getMI()->getIntr() | MI_INTR_SI);
			RCP::getSI()->setStatus(RCP::getSI()->getStatus() | SI_STATUS_INTERRUPT);
		    R4300i::check_interrupt();
			break;
		case 0x10:
			memset(data.pram,0,0x7C0);
			break;
		case 0x30:
			data.pram[0x3F] = 0x80;		
			break;
		case 0xC0:
			memset(data.pram,0,0x40);
			break;
		default:
			;
			/*if (ShowPifRamErrors)
				DisplayError("Unkown PifRam control: %d",PIF_Ram[0x3F]);*/
		}
		return;
	}

	while (CurPos < 0x40)
	{
		switch(data.pram[CurPos])
		{
			case 0x00: 
				Channel ++; 
				if (Channel > 6)
					CurPos = 0x40;
				break;
			case 0xFE: 
				CurPos = 0x40; 
				break;
			case 0xFF: 
			case 0xB4: 
			case 0x56: 
			case 0xB8: 
				break; /* ??? */
			default:
				if (!(data.pram[CurPos] & 0xC0)) 
				{
					if (Channel < 4) 
					{
						if (CONTROLLER::controllers[Channel].Present && CONTROLLER::controllers[Channel].RawData)
								CONTROLLER::controllerCommand(Channel,&data.pram[CurPos]);
						else
							ProcessControllerCommand(Channel,&data.pram[CurPos]);
					}
					/*else if (Channel == 4)
						EepromCommand(&data.pram[CurPos]);
					else 
						DebugError("Command on channel 5?");*/
					CurPos += data.pram[CurPos] + (data.pram[CurPos + 1] & 0x3F) + 1;
					Channel += 1;
				} 
				else 
				{
					//if (ShowPifRamErrors)
					//	DisplayError("Unknown Command in PifRamWrite(%X)",data.pram[CurPos]);
					CurPos = 0x40;
				}
				break;
		}
		CurPos++;
	}
//	data.pram[0x04] = 0x05;
//	data.pram[0x05] = 0x00;
//	data.pram[0x06] = 0x02;
//	data.pram[0x07] = 0xff;
	data.pram[0x3F] = 0;
	CONTROLLER::controllerCommand(-1,NULL);
}