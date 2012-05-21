#include "StdAfx.h"
#include "R4300i.h"

R4300i::R4300i(void) : ehandler(*new ExceptionHandler())
{
	SuperMario64 = "4080680040804800408058003C08A470250800008D09000C152000ED0000000027BDFFE8AFB30000AFB40004AFB50008AFB6000CAFB700103C08A470250800003C0AA3F83C0BA3F03C0CA430258C000034090040AD09000424111F40000000002231FFFF1620FFFD00000000AD00000834090014AD09000CAD00000024110004000000002231FFFF1620FFFD000000003409000EAD090000241100202231FFFF1620FFFE3409010FAD8900003C09180835292838AD490008AD4000143C098000AD49000400006825000070253C0FA3F00000C0253C19A3F03C16A0000000B8253C06A3F03C07A000000090253C14A00027BDFFB803A0F0253C10A4308E1000043C110101263101011611000500000000241002003571400010000003000000002410040035718000AE2E000425F5000C0D0001DE000000001040003800000000AFA2000024092000AD8900008DEB00003C08F0FF01685824AFAB000423BD000824091000AD8900003C08B0191568000C000000003C0808000308C0200330C8200330C8203C08002002C8B0200288A020001290402252000110000003000000003C0800100288A02024082000AD8800008DE900248DFA000024081000AD8800003129FFFF2408050015280009000000003C1B0100035BD02417400005000000003C08101C35080A04ADE80018100000033C08080C35081204ADE800183C08080001C8702001F0782001F0782025AD00012DA800081500FFC4000000003C08C400AD48000C3C088000AD48000403C0E825000018258FA900043C08B0091528001600000000AE3800042735000C8FA4000023BD0008240500010D000290000000008EC800003C080008011640208D0900008EC800003C080008011640208D0900003C08040001C870200330C8203C08001002C8B02010000021AE37000424D5000C8FA4000023BD0008240500010D000290000000008CE800003C080008010740208D0900003C080010010740208D0900003C080018010740208D0900008CE800003C080008010740208D0900003C080010010740208D0900003C080018010740208D0900003C08080002E8B82000D0302000D030203C08002000E8382024630001006D402A1500FFC3000000003C0AA470001294C03C0900063529363401324825AD4900108D4900103C08A000350803003C090FFF3529FFFF02C9B024AD16001803C0E82527BD00488FB300008FB400048FB500088FB6000C8FB7001027BD00183C08800025080000250940002529FFE04080E0004080E800BD0800000109082B1420FFFD250800203C08800025080000250920002529FFF0BD0900000109082B1420FFFD2508001010000013000000003C08800025080000250940002529FFE04080E0004080E800BD0800000109082B1420FFFD250800203C08800025080000250920002529FFF0BD0100000109082B1420FFFD250800103C0AA400254A00003C0BFFF03C090010014B50243C08A4002529FFFF3C0BA400250804C0256B077401094024016958243C09A000010A4025016A5825252900008D0D000025080004010B082B252900041420FFFBAD2DFFFC3C0C8000258C000001800008000000003C0BB0008D6900083C0A1FFF354AFFFF3C01A460012A4824AC2900003C08A4608D080010310800025500FFFD3C08A46024081000010B4020010A40243C01A460AC2800043C0A0010254AFFFF3C01A460AC2A000C000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000003C0BA4608D6B0010316B00011560FFE0000000003C0BB0008D64000802C028253C015D5834218B6500A1001927BDFFE0AFBF001CAFB000143C1F0010000018250000402500804825240D002000001012244200010040382500405025004058250040802500403025004060258D22000000E218210067082B1020000200602825254A00013043001F01A3782301E2C0060062700401D8202500C2082B00A0382501625826102000040204802100E2C826100000020326302600C43026250800040050782625290004151FFFE801EC602100EA702601CB38260206C026030C80263C0BB0008D68001014E80006000000008D680014160800030000000004110003000000000411FFFF000000003C09A4088D2900008FB000148FBF001C1120000627BD0020240A00413C01A404AC2A00103C01A408AC2000003C0B00AA356BAAAE3C01A404AC2B00103C01A43024080555AC28000C3C01A480AC2000183C01A450AC20000C3C01A43024090800AC290000240900023C01A4603C08A00035080300AC290010AD170014AD15000CAD13000412600004AD1400003C09A60010000003252900003C09B00025290000AD0900083C08A4002508000021091000250800041509FFFEAD00FFFC3C08A4002508100021091000250800041509FFFEAD00FFFC3C0BB0008D69000801200008000000000000000027BDFF60AFB00040AFB100440000882500008025AFA20000AFA30004AFA40008AFA5000CAFA60010AFA70014AFA80018AFA9001CAFAA0020AFAB0024AFAC0028AFAD002CAFAE0030AFAF0034AFB80038AFB9003CAFB20048AFB3004CAFB40050AFB50054AFB60058AFB7005CAFBE0060AFBF00640D00022000000000261000012A0900041520FFFB02228821001120820D000290240500018FBF0064001110828FB100448FA300048FA400088FA5000C8FA600108FA700148FA800188FA9001C8FAA00208FAB00248FAC00288FAD002C8FAE00308FAF00348FB800388FB9003C8FB000408FB200488FB3004C8FB400508FB500548FB600588FB7005C8FBE006003E0000827BD00A027BDFFE0AFBF001C000048250000582500006025299A004053400018000010250D0002430180202558400008293A00500049D023034C0019004048250000D012017A582100000000293A00501740FFF1258C0001000B2080008B202300042080008B2023000420400D0002602484FC90100000038FBF001C000010258FBF001C27BD002003E000080000000027BDFFD8AFBF001C000010250D000290240500020000F025241AFFFFAE9A00048E830004AE9A0000AE9A00000000E02500031C02307A000153400003279C000124420001279C00012B9A00081740FFF90003184227DE00012BDA000A5740FFEF241AFFFF8FBF001C27BD002803E000080000000027BDFFD8AFBF001CAFA40020A3A000270000402500005025340DC8000000702529DA00405740000401C02025100000200000102501C020250D000290240500010D0002B427A400270D0002B427A4002793BA0027241B03208FA40020035B0019000040120104D02307430003034DD82A0088D023034DD82A536000048FA400200340682501C050258FA400200104D82A53600006014E102125CE000129DB00415760FFE029DA0040014E1021000210428FBF001C27BD002803E000080000000027BDFFD8308400FF241B00013884003FAFBF001C14BB00033C0F46003C1A800001FA7825309A0001001AD18001FA7825309A0002001AD34001FA7825309A0004001AD50001FA7825309A0008001AD10001FA7825309A0010001AD2C001FA7825309A0020001AD48001FA7825241B000114BB0003AEAF00003C1AA430AF4000008FBF001C27BD002803E000080000000027BDFFD8AFBF001C241A20003C1BA430AF7A00000000F0258EBE0000241A1000AF7A0000241B0040037ED824001BD9820000D025035BD025241B4000037ED824001BDB42035BD0253C1B0040037ED824001BDD02035BD025241B0080037ED824001BD902035BD025341B8000037ED824001BDAC2035BD0253C1B0080037ED824001BDC82035BD025A09A00008FBF001C27BD002803E00008000000000000000002001001400A008804402202081041FF080840440120087F020410108084042041FE080840220110088044043FC00700C608088024014002001000800200900440418C03807E020C1010804402200900480240120110088084183F007FE20010008004002001FF080040020010008004003FF07FE20010008004002001FF0800400200100080040020000700C60808802401400200100083F200900440618D038840120090048024012009FFC8024012009004802401200807001000800400200100080040020010008004002003800040020010008004002001000800420210108082080F8040220210208204202201200A80620208102080840220084002001000800400200100080040020010008004003FF0800C007007405A02C826413111888C286143041820C0044023011408A044822211108844422209102881440620100F01861008804801400A005002801400900880430C07807F820210088044022011010FF0400200100080040020000F01861008804801400A005002801410904881430C07907F820210088044022021FE0820408204101080840220101F81021008804400100070007000400110088042040FC07FF010008004002001000800400200100080040020010040220110088044022011008804402201081040810807804012008808404202082041011008804401400A00200100820C1060828A2451228914451428A1450A282081040820401101041020808802800800400500440410208202200840110108082080880440140040020010008004002001007FE0010010010008008008008008008004004004003FF00F808208084042021010808404202101080840410407C002003002800400200100080040020010008004002001000F00840810408004002002002002002002002002001FE00F0084081040800400401C00100040020810408108078001001800C00A009004804404202102081FF802001000801F810008004002001780C20408004002081040810807800F008408104082001000BC0610204102081040810807803FC00200200100100080040040020010010008004002000F0084081040820408403C0210204102081040810807800F0084081040820410204301E8004002081040810807800200100080040020010008004002001000000000200100D806C0120120000000000000000000000000000000000004402201100887FF04402201100883FF84402201100880C006001001000000000000000000000000000000000000000000008044412405401C00400700540490444020000000000000800400200100080FFE02001000800400200000000000000000000000000000000000003001800400400000000000000000000000000FFE000000000000000000000000000000000000000000000000000030018000000000000000400400400400400400400400400400400400400000000000000C0060000000000000000001800C0000000000000000000000003FF80000000003FF8000000000000007004404102080040040040040020010000000002001000700C60808802431424A225122892236100240218603C0000000000000000000000000000000000000";
}

void R4300i::start(){
	char** PC = &SuperMario64;
	word i;
	while (*PC)
	{
		i = getWord(PC);
		cout << "Now decoding: " << i << endl;
		decode(i);
	}
}

void R4300i::decode(const word i)
{
	switch(getOpCode(i)) {
	case 0:
		decode_r(i);
		break;
	case 1:
		decode_i(i);
		break;
	case 2:
		J(getTarget(i));
		break;
	case 3:
		JAL(getTarget(i));
		break;
	case 4:
		BEQ(getRs(i), getRt(i), getImmediate(i));
		break;
	case 5:
		BNE(getRs(i), getRt(i), getImmediate(i));
		break;
	case 6:
		BLEZ(getRs(i), getImmediate(i));
		break;
	case 7:
		BGTZ(getRs(i), getImmediate(i));
		break;
	case 8:
		ADDI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 9:
		ADDIU(getRt(i), getRs(i), getImmediate(i));
		break;
	case 10:
		SLTI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 11:
		SLTIU(getRt(i), getRs(i), getImmediate(i));
		break;
	case 12:
		ANDI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 13:
		ORI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 14:
		XORI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 15:
		LUI(getRt(i), getImmediate(i));
		break;
	case 16:
		decode_cop0(i);
		break;
	case 17:
		decode_cop1(i);
		break;
	case 20:
		BEQL(getRs(i), getRt(i), getImmediate(i));
		break;
	case 21:
		BNEL(getRs(i), getRt(i), getImmediate(i));
		break;
	case 22:
		BLEZL(getImmediate(i), getRs(i));
		break;
	case 23:
		BGTZL(getImmediate(i), getRs(i));
		break;
	case 24:
		DADDI(getRt(i), getRs(i), getImmediate(i));
		break;
	case 25:
		DADDIU(getRt(i), getRs(i), getImmediate(i));
		break;
	case 26:
		LDL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 27:
		LDR(getRt(i), getImmediate(i), getRs(i));
		break;
	case 32:
		LB(getRt(i), getImmediate(i), getRs(i));
		break;
	case 33:
		LH(getRt(i), getImmediate(i), getRs(i));
		break;
	case 34:
		LWL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 35:
		LW(getRt(i), getImmediate(i), getRs(i));
		break;
	case 36:
		LBU(getRt(i), getImmediate(i), getRs(i));
		break;
	case 37:
		LHU(getRt(i), getImmediate(i), getRs(i));
		break;
	case 38:
		LWR(getRt(i), getImmediate(i), getRs(i));
		break;
	case 39:
		LWU(getRt(i), getImmediate(i), getRs(i));
		break;
	case 40:
		SB(getRt(i), getImmediate(i), getRs(i));
		break;
	case 41:
		SH(getRt(i), getImmediate(i), getRs(i));
		break;
	case 42:
		SWL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 43:
		SW(getRt(i), getImmediate(i), getRs(i));
		break;
	case 44:
		SDL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 45:
		SDR(getRt(i), getImmediate(i), getRs(i));
		break;
	case 46:
		SWR(getRt(i), getImmediate(i), getRs(i));
		break;
	case 47:
		CACHE(getRt(i), getImmediate(i), getRs(i));
		break;
	case 48:
		LL(getRt(i), getImmediate(i), getRs(i));
		break;
	case 49:
		LWC1(getRt(i), getImmediate(i), getRs(i));
		break;
	case 52:
		LLD(getRt(i), getImmediate(i), getRs(i));
		break;
	case 53:
		LDC1(getRt(i), getImmediate(i), getRs(i));
		break;
	case 54:
		//TODO: LDC2
		break;
	case 55:
		LD(getRt(i), getImmediate(i), getRs(i));
		break;
	case 56:
		SC(getRt(i), getImmediate(i), getRs(i));
		break;
	case 57:
		SWC1(getRt(i), getImmediate(i), getRs(i));
		break;
	case 60:
		SCD(getRt(i), getImmediate(i), getRs(i));
		break;
	case 61:
		SDC1(getRt(i), getImmediate(i), getRs(i));
		break;
	case 62:
		//TODO: SDC2
		break;
	case 63:
		SD(getRt(i), getImmediate(i), getRs(i));
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_r(word i)
{
	switch(getFunct(i)) {
	case 0:
		SLL(getRd(i), getRt(i), getSa(i));
		break;
	case 2:
		SRL(getRd(i), getRt(i), getSa(i));
		break;
	case 3:
		SRA(getRd(i), getRt(i), getSa(i));
		break;
	case 4:
		SLLV(getRd(i), getRt(i), getRs(i));
		break;
	case 6:
		SRLV(getRd(i), getRt(i), getRs(i));
		break;
	case 7:
		SRAV(getRd(i), getRt(i), getRs(i));
		break;
	case 8:
		JR(getRs(i));
		break;
	case 9:
		JALR(getRs(i), getRd(i));
		break;
	case 12:
		SYSCALL(getImmediate(i));
		break;
	case 13:
		BREAK(getImmediate(i));
		break;
	case 15:
		SYNC();
		break;
	case 16:
		MFHI(getRd(i));
		break;
	case 17:
		MTHI(getRd(i));
		break;
	case 18:
		MFLO(getRd(i));
		break;
	case 19:
		MTLO(getRd(i));
		break;
	case 20:
		DSLLV(getRd(i), getRt(i), getRs(i));
		break;
	case 22:
		DSRLV(getRd(i), getRt(i), getRs(i));
		break;
	case 23:
		DSRAV(getRd(i), getRt(i), getRs(i));
		break;
	case 24:
		MULT(getRs(i), getRt(i));
		break;
	case 25:
		MULTU(getRs(i), getRt(i));
		break;
	case 26:
		DIV(getRs(i), getRt(i));
		break;
	case 27:
		DIVU(getRs(i), getRt(i));
		break;
	case 28:
		DMULT(getRs(i), getRt(i));
		break;
	case 29:
		DMULTU(getRs(i), getRt(i));
		break;
	case 30:
		DDIV(getRs(i), getRt(i));
		break;
	case 31:
		DDIVU(getRs(i), getRt(i));
		break;
	case 32:
		ADD(getRd(i), getRs(i), getRt(i));
		break;
	case 33:
		ADDU(getRd(i), getRs(i), getRt(i));
		break;
	case 34:
		SUB(getRd(i), getRs(i), getRt(i));
		break;
	case 35:
		SUBU(getRd(i), getRs(i), getRt(i));
		break;
	case 36:
		AND(getRd(i), getRs(i), getRt(i));
		break;
	case 37:
		OR(getRd(i), getRs(i), getRt(i));
		break;
	case 38:
		XOR(getRd(i), getRs(i), getRt(i));
		break;
	case 39:
		NOR(getRd(i), getRs(i), getRt(i));
		break;
	case 42:
		SLT(getRd(i), getRs(i), getRt(i));
		break;
	case 43:
		SLTU(getRd(i), getRs(i), getRt(i));
		break;
	case 44:
		DADD(getRd(i), getRs(i), getRt(i));
		break;
	case 45:
		DADDU(getRd(i), getRs(i), getRt(i));
		break;
	case 46:
		DSUB(getRd(i), getRs(i), getRt(i));
		break;
	case 47:
		DSUBU(getRd(i), getRs(i), getRt(i));
		break;
	case 48:
		TGE(getRs(i), getRt(i));
		break;
	case 49:
		TGEU(getRs(i), getRt(i));
		break;
	case 50:
		TLT(getRs(i), getRt(i));
		break;
	case 51:
		TLTU(getRs(i), getRt(i));
		break;
	case 52:
		TEQ(getRs(i), getRt(i));
		break;
	case 54:
		TNE(getRs(i), getRt(i));
		break;
	case 56:
		DSLL(getRd(i), getRt(i), getSa(i));
		break;
	case 58:
		DSRL(getRd(i), getRt(i), getSa(i));
		break;
	case 59:
		DSRA(getRd(i), getRt(i), getSa(i));
		break;
	case 60:
		DSLL32(getRd(i), getRt(i), getSa(i));
		break;
	case 62:
		DSRL32(getRd(i), getRt(i), getSa(i));
		break;
	case 63:
		DSRA32(getRd(i), getRt(i), getSa(i));
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_i(word i)
{
	switch(getRt(i)) {
	case 0:
		BLTZ(getImmediate(i), getRs(i));
		break;
	case 1:
		BGEZ(getImmediate(i), getRs(i));
		break;
	case 2:
		BLTZL(getImmediate(i), getRs(i));
		break;
	case 3:
		BGEZL(getImmediate(i), getRs(i));
		break;
	case 8:
		TGEI(getRs(i), getImmediate(i));
		break;
	case 9:
		TGEIU(getRs(i), getImmediate(i));
		break;
	case 10:
		TLTI(getRs(i), getImmediate(i));
		break;
	case 11:
		TLTIU(getRs(i), getImmediate(i));
		break;
	case 12:
		TEQI(getRs(i), getImmediate(i));
		break;
	case 14:
		TNEI(getRs(i), getImmediate(i));
		break;
	case 16:
		BLTZAL(getImmediate(i), getRs(i));
		break;
	case 17:
		BGEZAL(getImmediate(i), getRs(i));
		break;
	case 18:
		BLTZALL(getImmediate(i), getRs(i));
		break;
	case 19:
		BGEZALL(getImmediate(i), getRs(i));
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_cop0(word i)
{
	switch(getRs(i)) {
	case 0:
		MFC0(getRt(i), getRd(i));
		break;
	case 4:
		MTC0(getRt(i), getRd(i));
		break;
	case 16:
		decode_tlb(i);
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_tlb(word i)
{
	switch(getFunct(i)) {
	case 1:
		TLBR();
		break;
	case 2:
		TLBWI();
		break;
	case 6:
		TLBWR();
		break;
	case 8:
		TLBP();
		break;
	case 24:
		ERET();
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_cop1(const word i)
{
	switch(getRs(i)) {
	case 0:
		MFC1(getRt(i), getRd(i));
		break;
	case 1:
		DMFC1(getRt(i), getRd(i));
		break;
	case 2:
		CFC1(getRt(i), getRd(i));
		break;
	case 4:
		MTC1(getRt(i), getRd(i));
		break;
	case 5:
		DMTC1(getRt(i), getRd(i));
		break;
	case 6:
		CTC1(getRt(i), getRd(i));
		break;
	case 8:
		decode_bc1(i);
		break;
	case 16:
		decode_fpu<s>(i);
		break;
	case 17:
		decode_fpu<d>(i);
		break;
	case 20:
		decode_fpu<w>(i);
		break;
	case 21:
		decode_fpu<l>(i);
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

inline void R4300i::decode_bc1(const word i)
{
	switch(getNdTf(i)) {
	case 0:
		BC1F(getImmediate(i));
		break;
	case 1:
		BC1T(getImmediate(i));
		break;
	case 2:
		BC1FL(getImmediate(i));
		break;
	case 3:
		BC1TL(getImmediate(i));
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

template<typename Type>
inline void R4300i::decode_fpu(const word i)
{
	switch(getFunct(i)) {
	case 0:
		ADD<Type>(getSa(i), getRd(i), getRt(i));
		break;
	case 1:
		SUB<Type>(getSa(i), getRd(i), getRt(i));
		break;
	case 2:
		MUL<Type>(getSa(i), getRd(i), getRt(i));
		break;
	case 3:
		DIV<Type>(getSa(i), getRd(i), getRt(i));
		break;
	case 4:
		SQRT<Type>(getSa(i), getRd(i));
		break;
	case 5:
		ABS<Type>(getSa(i), getRd(i));
		break;
	case 6:
		MOV<Type>(getSa(i), getRd(i));
		break;
	case 7:
		NEG<Type>(getSa(i), getRd(i));
		break;
	case 8:
		ROUND<Type, l>(getSa(i), getRd(i));
		break;
	case 9:
		TRUNC<Type, l>(getSa(i), getRd(i));
		break;
	case 10:
		CEIL<Type, l>(getSa(i), getRd(i));
		break;
	case 11:
		FLOOR<Type, l>(getSa(i), getRd(i));
		break;
	case 12:
		ROUND<Type, w>(getSa(i), getRd(i));
		break;
	case 13:
		TRUNC<Type, w>(getSa(i), getRd(i));
		break;
	case 14:
		CEIL<Type, w>(getSa(i), getRd(i));
		break;
	case 15:
		FLOOR<Type, w>(getSa(i), getRd(i));
		break;
	case 32:
		CVT<Type, s>(getSa(i), getRd(i));
		break;
	case 33:
		CVT<Type, d>(getSa(i), getRd(i));
		break;
	case 36:
		CVT<Type, w>(getSa(i), getRd(i));
		break;
	case 37:
		CVT<Type, l>(getSa(i), getRd(i));
		break;
	case 48:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 49:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 50:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 51:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 52:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 53:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 54:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 55:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 56:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 57:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 58:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 59:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 60:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 61:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 62:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	case 63:
		C<Type>(getRd(i), getRt(i), getCond(i));
		break;
	default:
		ExceptionHandler::unknownInstruction(i);
	}
}

void R4300i::LB(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LBU(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LD(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LDL(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LDR(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LH(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LHU(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LL(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LLD(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LW(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LWL(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LWR(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::LWU(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SB(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SC(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SCD(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SD(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SDL(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SDR(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SH(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SW(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SWL(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SWR(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::SYNC(void)
{
	// TODO
}

void R4300i::ADD(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::ADDI(int rt, int rs, int immed)
{
	if (DWORD_MAX - immed < r[rs])
	{
		//TODO: "If overflow occurs, then trap."
		ehandler.trap();
	}
	else
	{
		r[rt] = r[rs] + immed;
	}
}

void R4300i::ADDIU(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::ADDU(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::AND(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::ANDI(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::DADD(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::DADDI(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::DADDIU(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::DADDU(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::DDIV(int rs, int rt)
{
	// TODO
}

void R4300i::DDIVU(int rs, int rt)
{
	// TODO
}

void R4300i::DIV(int rs, int rt)
{
	// TODO
}

void R4300i::DIVU(int rs, int rt)
{
	// TODO
}

void R4300i::DMULT(int rs, int rt)
{
	// TODO
}

void R4300i::DMULTU(int rs, int rt)
{
	// TODO
}

void R4300i::DSLL(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::DSLL32(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::DSLLV(int rd, int rt, int rs)
{
	// TODO
}

void R4300i::DSRA(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::DSRA32(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::DSRAV(int rd, int rt, int rs)
{
	// TODO
}

void R4300i::DSRL(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::DSRL32(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::DSRLV(int rd, int rt, int rs)
{
	// TODO
}

void R4300i::DSUB(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::DSUBU(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::LUI(int rt, int immed)
{
	// TODO
}

void R4300i::MFHI(int rd)
{
	// TODO
}

void R4300i::MFLO(int rd)
{
	// TODO
}

void R4300i::MTHI(int rd)
{
	// TODO
}

void R4300i::MTLO(int rd)
{
	// TODO
}

void R4300i::MULT(int rs, int rt)
{
	// TODO
}

void R4300i::MULTU(int rs, int rt)
{
	// TODO
}

void R4300i::NOR(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::OR(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::ORI(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::SLL(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::SLLV(int rd, int rt, int rs)
{
	// TODO
}

void R4300i::SLT(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::SLTI(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::SLTIU(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::SLTU(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::SRA(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::SRAV(int rd, int rt, int rs)
{
	// TODO
}

void R4300i::SRL(int rd, int rt, int sa)
{
	// TODO
}

void R4300i::SRLV(int rd, int rt, int rs)
{
	// TODO
}

void R4300i::SUB(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::SUBU(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::XOR(int rd, int rs, int rt)
{
	// TODO
}

void R4300i::XORI(int rt, int rs, int immed)
{
	// TODO
}

void R4300i::BEQ(int rs, int rt, int immed)
{
	// TODO
}

void R4300i::BEQL(int rs, int rt, int immed)
{
	// TODO
}

void R4300i::BGEZ(int immed, int rs)
{
	// TODO
}

void R4300i::BGEZAL(int immed, int rs)
{
	// TODO
}

void R4300i::BGEZALL(int immed, int rs)
{
	// TODO
}

void R4300i::BGEZL(int immed, int rs)
{
	// TODO
}

void R4300i::BGTZ(int immed, int rs)
{
	// TODO
}

void R4300i::BGTZL(int immed, int rs)
{
	// TODO
}

void R4300i::BLEZ(int immed, int rs)
{
	// TODO
}

void R4300i::BLEZL(int immed, int rs)
{
	// TODO
}

void R4300i::BLTZ(int immed, int rs)
{
	// TODO
}

void R4300i::BLTZAL(int immed, int rs)
{
	// TODO
}

void R4300i::BLTZALL(int immed, int rs)
{
	// TODO
}

void R4300i::BLTZL(int immed, int rs)
{
	// TODO
}

void R4300i::BNE(int rs, int rt, int immed)
{
	// TODO
}

void R4300i::BNEL(int rs, int rt, int immed)
{
	// TODO
}

void R4300i::J(int address)
{
	// TODO
}

void R4300i::JAL(int address)
{
	// TODO
}

void R4300i::JALR(int rs, int rd)
{
	// TODO
}

void R4300i::JR(int rs)
{
	// TODO
}

void R4300i::BREAK(int immed)
{
	// TODO
}

void R4300i::SYSCALL(int immed)
{
	// TODO
}

void R4300i::TEQ(int rs, int rt)
{
	// TODO
}

void R4300i::TEQI(int rs, int immed)
{
	// TODO
}

void R4300i::TGE(int rs, int rt)
{
	// TODO
}

void R4300i::TGEI(int rs, int immed)
{
	// TODO
}

void R4300i::TGEIU(int rs, int immed)
{
	// TODO
}

void R4300i::TGEU(int rs, int rt)
{
	// TODO
}

void R4300i::TLT(int rs, int rt)
{
	// TODO
}

void R4300i::TLTI(int rs, int immed)
{
	// TODO
}

void R4300i::TLTIU(int rs, int immed)
{
	// TODO
}

void R4300i::TLTU(int rs, int rt)
{
	// TODO
}

void R4300i::TNE(int rs, int rt)
{
	// TODO
}

void R4300i::TNEI(int rs, int immed)
{
	// TODO
}

void R4300i::CACHE(int rt, int immed, int rs)
{
	// TODO
}

void R4300i::ERET(void)
{
	// TODO
}

void R4300i::MFC0(int rt, int fs)
{
	// TODO
}

void R4300i::MTC0(int rt, int fs)
{
	// TODO
}

void R4300i::TLBP(void)
{
	// TODO
}

void R4300i::TLBR(void)
{
	// TODO
}

void R4300i::TLBWI(void)
{
	// TODO
}

void R4300i::TLBWR(void)
{
	// TODO
}

template<typename Type>
void R4300i::ABS(int fd, int fs)
{
	// TODO
}

template<typename Type>
void R4300i::ADD(int fd, int fs, int ft)
{
	// TODO
}

void R4300i::BC1F(int immed)
{
	// TODO
}

void R4300i::BC1FL(int immed)
{
	// TODO
}

void R4300i::BC1T(int immed)
{
	// TODO
}

void R4300i::BC1TL(int immed)
{
	// TODO
}

template<typename Type>
void R4300i::C(int fs, int ft, int cond)
{
	// TODO
	switch (cond) {
	case 0:
		F<Type>(f[fs], f[ft]);
	case 1:
		UN<Type>(f[fs], f[ft]);
	case 2:
		EQ<Type>(f[fs], f[ft]);
		//...
	default:
		// ERROR
		;
	}
}

template<typename Type, typename toType>
void R4300i::CEIL(int fd, int fs)
{
	// TODO
}

void R4300i::CFC1(int rt, int fs)
{
	// TODO
}

void R4300i::CTC1(int rt, int fs)
{
	// TODO
}

template<typename Type, typename toType>
void R4300i::CVT(int fd, int fs)
{
	// TODO
}

template<typename Type>
void R4300i::DIV(int fd, int fs, int ft)
{
	// TODO
}

void R4300i::DMFC1(int rt, int fs)
{
	// TODO
}

void R4300i::DMTC1(int rt, int fs)
{
	// TODO
}

template<typename Type, typename toType>
void R4300i::FLOOR(int fd, int fs)
{
	// TODO
}

void R4300i::LDC1(int ft, int immed, int rs)
{
	// TODO
}

void R4300i::LWC1(int ft, int immed, int rs)
{
	// TODO
}

void R4300i::MFC1(int rt, int fs)
{
	// TODO
}

template<typename Type>
void R4300i::MOV(int fd, int fs)
{
	// TODO
}

void R4300i::MTC1(int rt, int fs)
{
	// TODO
}

template<typename Type>
void R4300i::MUL(int fd, int fs, int ft)
{
	// TODO
}

template<typename Type>
void R4300i::NEG(int fd, int fs)
{
	// TODO
}

template<typename Type, typename toType>
void R4300i::ROUND(int fd, int fs)
{
	// TODO
}

void R4300i::SDC1(int ft, int immed, int rs)
{
	// TODO
}

template<typename Type>
void R4300i::SQRT(int fd, int fs)
{
	// TODO
}

template<typename Type>
void R4300i::SUB(int fd, int fs, int ft)
{
	// TODO
}

void R4300i::SWC1(int ft, int immed, int rs)
{
	// TODO
}

template<typename Type, typename toType>
void R4300i::TRUNC(int fd, int fs)
{
	// TODO
}

void R4300i::NOP(void)
{
	// TODO
}

void R4300i::MOVE(int rd, int rs)
{
	// TODO
}

void R4300i::NEG(int rd, int rt)
{
	// TODO
}

void R4300i::NEGU(int rd, int rs)
{
	// TODO
}

void R4300i::BNEZ(int immed, int rs)
{
	// TODO
}

void R4300i::BNEZL(int immed, int rs)
{
	// TODO
}

void R4300i::BEQZ(int immed, int rs)
{
	// TODO
}

void R4300i::BEQZL(int immed, int rs)
{
	// TODO
}

void R4300i::B(int immed)
{
	// TODO
}

void R4300i::BAL(int immed)
{
	// TODO
}

void R4300i::LI(int rt, int immed)
{
	// TODO
}

void R4300i::S_S(int ft, int immed, int rs)
{
	// TODO
}

void R4300i::L_S(int ft, int immed, int rs)
{
	// TODO
}

template<typename Type>
bool R4300i::F(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::UN(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::EQ(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::UEQ(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::OLT(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::ULT(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::OLE(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::ULE(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::SF(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::NGLE(Type a, Type b)
{
	// TODO
	return true;
}


template<typename Type>
bool R4300i::SEQ(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::NGL(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool LT(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::NGE(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::LE(Type a, Type b)
{
	// TODO
	return true;
}

template<typename Type>
bool R4300i::NGT(Type a, Type b)
{
	// TODO
	return true;
}

