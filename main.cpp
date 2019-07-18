/*************************Touhou Japari***********************/
/*版    本:	Beta 1.1.9 										 */
/*最后修订:	2017/9/3										 */
/*作    者:	仝易寒 16160500301								 */
/*邮    箱:	icyqwq@gmail.com / tongyihan@pcb.moe			 */
/*************************************************************/

#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

/*************参数设定*************/
#define CheckPoint printf("Check Point :%u\n",++DebugTestPoint);
//模式设定 
//#define ENABLE_DebugMode	
/*#define ENABLE_Monitor	*/
/*#define DISABLE_CMD		*/
#define ENABLE_LWSetMode
#define ENABLE_ExpandAxis_Mode
#define ENABLE_Music
/*#define ENABLE_Aux_Frame	*/
/*#define ENABLE_AuxiliaryGrid			60*/
//系统参数设定
#define System_RefreshRate 				1000
#define WindowSize_L 					1020
#define WindowSize_H 					660
#define ShiftScreen_L_Xlocation			180
#define ShiftScreen_R_Xlocation			720
//操作设定
#define Keyboard_Jump 					0x57	//W
#define Keyboard_MoveLeft 				0x41	//A
#define Keyboard_Defense				0x53	//S
#define Keyboard_MoveRight 				0x44	//D
#define Keyboard_NorAtk					0x4A	//J
#define Keyboard_SkillA					0x4B	//K
#define Keyboard_SkillB					0x4C	//L
#define Keyboard_Barrage				0x55	//U
//玩家参数设定 
#define Remilia_JumpHeight				250
#define Remilia_JumpDelay				100
#define Remilia_initX					150
#define Remilia_initY		  		   	450
#define Remilia_Length					60
#define Remilia_Width					95
#define Remilia_HP						7000
#define Str_RemiliaHP					"/7000"
#define Remilia_MP						6000
#define Str_RemiliaMP					"/6000"
#define RemMPRestore_Speed				100
#define Remilia_Defense					125
#define Remilia_DeathSpeed				8
#define Remilia_BeatenSpeed				20
#define Remilia_DefensSpeed				40
//宏定义值 
#define X_Positive 						1
#define X_Negative 					   -1
#define Y_Positive 						2
#define Y_Negative 					   -2
#define L								0
#define R								1
#define ArcToAngle_Value 				57.2957796f
#define AngleToArc_Value 				0.01745329f
//普通攻击参数
#define NorAtk_CD							90 
#define NorAtk_Damage_A						150
#define NorAtk_Damage_B						180
#define NorAtk_Damage_C						240
#define NorAtk_DamRangeOff_X				0
#define NorAtk_DamRangeOff_Y				16
#define NorAtk_DamOffset_Y					5
#define NorAtkC_DamOffset_Y					25
#define NorAtk_TypeTimGap					130

#define Anime_NorAtkAct_Speed				25
#define Anime_NorAtkEft_Speed				4
#define Anime_NorAtkEft_OffX_AR				27
#define Anime_NorAtkEft_OffY_AR				27
#define Anime_NorAtkEft_OffX_CR				32
#define Anime_NorAtkEft_OffY_CR				0
#define Anime_NorAtkAct_OffX_AR				27
#define Anime_NorAtkAct_OffY_AR				22
#define Anime_NorAtkAct_OffX_CR				24
#define Anime_NorAtkAct_OffY_CR				8
#define Anime_NorAtkEft_OffX_AL				27
#define Anime_NorAtkEft_OffY_AL				27
#define Anime_NorAtkEft_OffX_CL				64
#define Anime_NorAtkEft_OffY_CL				0
#define Anime_NorAtkAct_OffX_AL				27
#define Anime_NorAtkAct_OffY_AL				22
#define Anime_NorAtkAct_OffX_CL				24
#define Anime_NorAtkAct_OffY_CL				8
//技能A参数
#define SkillA_CD							400//800
#define SkillA_MP							200//400
#define SkillA_Damage						300
#define SkillA_DamRangeOff_X				0
#define SkillA_DamRangeOff_Y				0

#define Anime_SkillA_Speed					15
#define Anime_SkillEffect_InitX				64
#define Anime_SkillEffect_XGap				2
//技能B参数 
#define SkillB_CD							1000//3000
#define SkillB_MP							400//800
#define SkillB_Damage						800
#define SkillB_DamRangeOff_X				32
#define SkillB_DamRangeOff_Y				96

#define Anime_SkillB_Speed					15
#define Anime_SkillBArrow_Speed				8
#define Anime_SkillBArrow_XGap				3
#define Anime_SkillB_LeftXoffset			192
#define Anime_SkillB_RightXoffset			64
#define Anime_RemSkillBOffset_X				36
#define Anime_RemSkillBOffset_Y				21
#define Anime_RemSkillBOffset_Effect_Y		64
#define Anime_SkillHitEffect_Speed			10
#define Anime_SkillBHitEffect_Offset_X		32
#define Anime_SkillBHitEffect_Offset_Y		32
#define Anime_BossHitEffect_Offset_X		40
#define Anime_BossHitEffect_Offset_Y		40
//大招参数
#define SkillBarrage_CD						5000//10000
#define SkillBarrage_MP						700//1400
#define SkillBarrage_Damage					15
#define SkillBarrage_Type					3

#define SkillBarrage_Density				150
#define SkillBarrage_RadGap					8
#define SkillBarrage_Speed					2
#define SkillBarrage_Height					300
#define SkillBarrage_ActSpeed				40
#define SkillBarrage_AngGap					5.0f
#define SkillBarrage_AngFluc				15
#define SkillBarrage_AngStart				0//中轴角度 
#define SkillBarrage_AngEnd					35//扩散角度 
//Cerulean参数
#define Enemy_CeruleanBlue_Life				400
#define Enemy_CeruleanBlue_Damage			150
#define Enemy_CeruleanBlue_Number			10
#define Enemy_CeruBlue_AttTimGap			1000
#define Anime_CeruBlue_AttSpeed				20
#define Enemy_CeruleanBlue_DeathSpeed		50
#define Anime_CerBlue_DeathOffX				128
#define Anime_CerBlue_DeathOffY				64
#define Enemy_CeruleanBlue_Speed			5
#define Anime_CeruleanBlue_Speed			20
#define Anime_CeruleanBlueOffset_X			16
#define Anime_CeruleanBlueOffset_Y			18
#define Anime_CerBlue_AttOffsetX_R			20
#define Anime_CerBlue_AttOffsetX_L			20
#define Anime_CerBlue_AttOffsetY			0

#define Enemy_CeruleanPink_Life				300
#define Enemy_CeruleanPink_Damage			200
#define Enemy_CeruleanPink_Number			11
#define Enemy_CeruleanPink_JumpHeight		360
#define Enemy_CeruleanPink_Speed			8

#define Props_ReplyHp_AnimeSpeed			12
#define Props_ReplyHp_Value					250
#define Props_ReplyHp_Value_Str				"+500"
//Boss参数
#define Enemy_BoosHP						10000
#define Str_BossHP							"/10000"
#define Enemy_BossMove_Speed				15
#define Enemy_BossAtk_CD					1000

#define BossAtk_Laser_Speed					30
#define BossAtk_Laser_OffsetX				810
#define BossAtk_Laser_OffsetY				20
#define BossAtk_Laser_Damage				50

#define BossAtk_Barrage_Damage				2
#define BossAtk_Barrage_Density				183
#define BossAtk_Barrage_Gap					5
#define BossAtk_Barrage_Speed				0
#define BossAtk_Barrage_Ang_GapT1			30
#define BossAtk_Barrage_Ang_GapT2			7
#define BossAtk_Barrage_Ang_GapT3			7
#define BossAtk_Barrage_Ang_GapT4			20
#define BossAtk_Barrage_Ang_Start			150	//起始角度 
#define BossAtk_Barrage_Ang_End				210	//结束角度 
#define BossAtk_Barrage_Ang_Fluc			15	//波动角度 

#define BossAtk_Tentacle_Damage				500
#define BossAtk_Tentacle_Speed				100
#define BossAtk_Tentacle_Amount				3

#define Anime_BossActive_OffsetX			71
#define Anime_BossActive_OffsetY			76
#define Anime_BossMove_OffsetY				Remilia.y - 64
#define Anime_BossActive_Speed				25
#define Anime_BossDeath_Speed				25
//运动参数 
#define Anime_Move_Speed					50
#define Anime_RemMoveOffset_X				45
#define Anime_RemMoveOffset_Y				32
#define Anime_RemStandOffset_X				27
#define Anime_RemStandOffset_Y				30
//GUI定位参数
#define AREA_GameOver 						479,342,785,408
#define AREA_Start_1						334,470,684,560
#define AREA_Victory						800,569,996,636
//其它
#define ProgressBar(x)		\
		bar(0,640,x,660);	\
		delay_fps(60);
#define Anime_JapariProp_Speed 10;

//动画定位参数 
#define Anime_RemMovePara_L1 				0,0,128,128
#define Anime_RemMovePara_L2				127,0,128,128
#define Anime_RemMovePara_L3 				254,0,128,128
#define Anime_RemMovePara_L4 				381,0,128,128
#define Anime_RemMovePara_L5 				508,0,128,128
#define Anime_RemMovePara_L6 				0,127,128,128
#define Anime_RemMovePara_L7 				127,127,128,128
#define Anime_RemMovePara_L8 				254,127,128,128
#define Anime_RemMovePara_L9 				381,127,128,128
#define Anime_RemMovePara_R1 				508,127,128,128
#define Anime_RemMovePara_R2 				0,254,128,128
#define Anime_RemMovePara_R3 				127,254,128,128
#define Anime_RemMovePara_R4 				254,254,128,128
#define Anime_RemMovePara_R5 				381,254,128,128
#define Anime_RemMovePara_R6 				508,254,128,128
#define Anime_RemMovePara_R7 				0,381,128,128
#define Anime_RemMovePara_R8 				127,381,128,128

#define Anime_RemNorAtk_A_R1				0,0,128,128
#define Anime_RemNorAtk_A_R2				192,0,128,128
#define Anime_RemNorAtk_A_R3				384,0,128,128
#define Anime_RemNorAtk_A_R4				576,0,128,128
#define Anime_RemNorAtk_A_R5				768,0,128,128
#define Anime_RemNorAtk_A_R6				0,192,128,128
#define Anime_RemNorAtk_B_R1				192,192,128,128
#define Anime_RemNorAtk_B_R2				384,192,128,128
#define Anime_RemNorAtk_B_R3				576,192,128,128
#define Anime_RemNorAtk_B_R4				768,192,128,128
#define Anime_RemNorAtk_B_R5				0,384,128,128
#define Anime_RemNorAtk_B_R6				192,384,128,128
#define Anime_RemNorAtk_C_R1				384,384,128,128
#define Anime_RemNorAtk_C_R2				576,384,128,128
#define Anime_RemNorAtk_C_R3				768,384,128,128
#define Anime_RemNorAtk_C_R4				0,576,128,128
#define Anime_RemNorAtk_C_R5				192,576,128,128
#define Anime_RemNorAtk_C_R6				384,576,128,128
#define Anime_RemNorAtk_C_R7				576,576,128,128
#define Anime_RemNorAtk_C_R8				768,576,146,128
#define Anime_RemNorAtk_C_R9				0,768,155,128
#define Anime_RemNorAtk_C_R10				192,768,143,128
#define Anime_NorAtkEft_A_R1				384,768,128,128
#define Anime_NorAtkEft_A_R2				576,768,128,128
#define Anime_NorAtkEft_A_R3				768,768,128,128
#define Anime_NorAtkEft_A_R4				0,960,128,128
#define Anime_NorAtkEft_A_R5				192,960,128,128
#define Anime_NorAtkEft_A_R6				384,960,128,128
#define Anime_NorAtkEft_A_R7				576,960,128,128
#define Anime_NorAtkEft_A_R8				768,960,128,128
#define Anime_NorAtkEft_A_R9				0,1152,128,128
#define Anime_NorAtkEft_A_R10				192,1152,128,128
#define Anime_NorAtkEft_A_R11				384,1152,128,128
#define Anime_NorAtkEft_A_R12				576,1152,128,128
#define Anime_NorAtkEft_A_R13				768,1152,128,128
#define Anime_NorAtkEft_A_R14				0,1344,128,128
#define Anime_NorAtkEft_A_R15				192,1344,128,128
#define Anime_NorAtkEft_A_R16				384,1344,128,128
#define Anime_NorAtkEft_A_R17				576,1344,128,128
#define Anime_NorAtkEft_A_R18				768,1344,128,128
#define Anime_NorAtkEft_A_R19				0,1536,128,128
#define Anime_NorAtkEft_A_R20				192,1536,128,128
#define Anime_NorAtkEft_A_R21				384,1536,128,128
#define Anime_NorAtkEft_A_R22				576,1536,128,128
#define Anime_NorAtkEft_A_R23				768,1536,128,128
#define Anime_NorAtkEft_A_R24				0,1728,128,128
#define Anime_NorAtkEft_B_R1				192,1728,128,128
#define Anime_NorAtkEft_B_R2				384,1728,128,128
#define Anime_NorAtkEft_B_R3				576,1728,128,128
#define Anime_NorAtkEft_B_R4				768,1728,128,128
#define Anime_NorAtkEft_B_R5				0,1920,128,128
#define Anime_NorAtkEft_B_R6				192,1920,128,128
#define Anime_NorAtkEft_B_R7				384,1920,128,128
#define Anime_NorAtkEft_B_R8				576,1920,128,128
#define Anime_NorAtkEft_B_R9				768,1920,128,128
#define Anime_NorAtkEft_B_R10				0,2112,128,128
#define Anime_NorAtkEft_B_R11				192,2112,128,128
#define Anime_NorAtkEft_B_R12				384,2112,128,128
#define Anime_NorAtkEft_B_R13				576,2112,128,128
#define Anime_NorAtkEft_B_R14				768,2112,128,128
#define Anime_NorAtkEft_B_R15				0,2304,128,128
#define Anime_NorAtkEft_B_R16				192,2304,128,128
#define Anime_NorAtkEft_B_R17				384,2304,128,128
#define Anime_NorAtkEft_B_R18				576,2304,128,128
#define Anime_NorAtkEft_B_R19				768,2304,128,128
#define Anime_NorAtkEft_B_R20				0,2496,128,128
#define Anime_NorAtkEft_B_R21				192,2496,128,128
#define Anime_NorAtkEft_B_R22				384,2496,128,128
#define Anime_NorAtkEft_B_R23				576,2496,128,128
#define Anime_NorAtkEft_B_R24				768,2496,128,128
#define Anime_NorAtkEft_C_R1				0,2688,128,128
#define Anime_NorAtkEft_C_R2				192,2688,128,128
#define Anime_NorAtkEft_C_R3				384,2688,128,128
#define Anime_NorAtkEft_C_R4				576,2688,128,128
#define Anime_NorAtkEft_C_R5				768,2688,128,128
#define Anime_NorAtkEft_C_R6				0,2880,128,128
#define Anime_NorAtkEft_C_R7				192,2880,128,128
#define Anime_NorAtkEft_C_R8				384,2880,128,128
#define Anime_NorAtkEft_C_R9				576,2880,128,128
#define Anime_NorAtkEft_C_R10				768,2880,128,128
#define Anime_NorAtkEft_C_R11				0,3072,128,128
#define Anime_NorAtkEft_C_R12				192,3072,128,128
#define Anime_NorAtkEft_C_R13				384,3072,128,128
#define Anime_NorAtkEft_C_R14				576,3072,128,128
#define Anime_NorAtkEft_C_R15				768,3072,128,128
#define Anime_NorAtkEft_C_R16				0,3264,128,128
#define Anime_NorAtkEft_C_R17				192,3264,128,128
#define Anime_NorAtkEft_C_R18				384,3264,128,128
#define Anime_NorAtkEft_C_R19				576,3264,128,128
#define Anime_NorAtkEft_C_R20				768,3264,128,128
#define Anime_NorAtkEft_C_R21				0,3456,128,128
#define Anime_NorAtkEft_C_R22				192,3456,128,128
#define Anime_NorAtkEft_C_R23				384,3456,128,128
#define Anime_NorAtkEft_C_R24				576,3456,128,128
#define Anime_RemNorAtk_A_L1				832,0,128,128
#define Anime_RemNorAtk_A_L2				640,0,128,128
#define Anime_RemNorAtk_A_L3				448,0,128,128
#define Anime_RemNorAtk_A_L4				256,0,128,128
#define Anime_RemNorAtk_A_L5				64,0,128,128
#define Anime_RemNorAtk_A_L6				832,192,128,128
#define Anime_RemNorAtk_B_L1				640,192,128,128
#define Anime_RemNorAtk_B_L2				448,192,128,128
#define Anime_RemNorAtk_B_L3				256,192,128,128
#define Anime_RemNorAtk_B_L4				64,192,128,128
#define Anime_RemNorAtk_B_L5				832,384,128,128
#define Anime_RemNorAtk_B_L6				640,384,128,128
#define Anime_RemNorAtk_C_L1				448,384,128,128
#define Anime_RemNorAtk_C_L2				256,384,128,128
#define Anime_RemNorAtk_C_L3				64,384,128,128
#define Anime_RemNorAtk_C_L4				832,576,128,128
#define Anime_RemNorAtk_C_L5				640,576,128,128
#define Anime_RemNorAtk_C_L6				448,576,128,128
#define Anime_RemNorAtk_C_L7				256,576,128,128
#define Anime_RemNorAtk_C_L8				28,576,128,128
#define Anime_RemNorAtk_C_L9				777,768,128,128
#define Anime_RemNorAtk_C_L10				610,768,128,128
#define Anime_NorAtkEft_A_L1				448,768,128,128
#define Anime_NorAtkEft_A_L2				256,768,128,128
#define Anime_NorAtkEft_A_L3				64,768,128,128
#define Anime_NorAtkEft_A_L4				832,960,128,128
#define Anime_NorAtkEft_A_L5				640,960,128,128
#define Anime_NorAtkEft_A_L6				448,960,128,128
#define Anime_NorAtkEft_A_L7				256,960,128,128
#define Anime_NorAtkEft_A_L8				64,960,128,128
#define Anime_NorAtkEft_A_L9				832,1152,128,128
#define Anime_NorAtkEft_A_L10				640,1152,128,128
#define Anime_NorAtkEft_A_L11				448,1152,128,128
#define Anime_NorAtkEft_A_L12				256,1152,128,128
#define Anime_NorAtkEft_A_L13				64,1152,128,128
#define Anime_NorAtkEft_A_L14				832,1344,128,128
#define Anime_NorAtkEft_A_L15				640,1344,128,128
#define Anime_NorAtkEft_A_L16				448,1344,128,128
#define Anime_NorAtkEft_A_L17				256,1344,128,128
#define Anime_NorAtkEft_A_L18				64,1344,128,128
#define Anime_NorAtkEft_A_L19				832,1536,128,128
#define Anime_NorAtkEft_A_L20				640,1536,128,128
#define Anime_NorAtkEft_A_L21				448,1536,128,128
#define Anime_NorAtkEft_A_L22				256,1536,128,128
#define Anime_NorAtkEft_A_L23				64,1536,128,128
#define Anime_NorAtkEft_A_L24				832,1728,128,128
#define Anime_NorAtkEft_B_L1				640,1728,128,128
#define Anime_NorAtkEft_B_L2				448,1728,128,128
#define Anime_NorAtkEft_B_L3				256,1728,128,128
#define Anime_NorAtkEft_B_L4				64,1728,128,128
#define Anime_NorAtkEft_B_L5				832,1920,128,128
#define Anime_NorAtkEft_B_L6				640,1920,128,128
#define Anime_NorAtkEft_B_L7				448,1920,128,128
#define Anime_NorAtkEft_B_L8				256,1920,128,128
#define Anime_NorAtkEft_B_L9				64,1920,128,128
#define Anime_NorAtkEft_B_L10				832,2112,128,128
#define Anime_NorAtkEft_B_L11				640,2112,128,128
#define Anime_NorAtkEft_B_L12				448,2112,128,128
#define Anime_NorAtkEft_B_L13				256,2112,128,128
#define Anime_NorAtkEft_B_L14				64,2112,128,128
#define Anime_NorAtkEft_B_L15				832,2304,128,128
#define Anime_NorAtkEft_B_L16				640,2304,128,128
#define Anime_NorAtkEft_B_L17				448,2304,128,128
#define Anime_NorAtkEft_B_L18				256,2304,128,128
#define Anime_NorAtkEft_B_L19				64,2304,128,128
#define Anime_NorAtkEft_B_L20				832,2496,128,128
#define Anime_NorAtkEft_B_L21				640,2496,128,128
#define Anime_NorAtkEft_B_L22				448,2496,128,128
#define Anime_NorAtkEft_B_L23				256,2496,128,128
#define Anime_NorAtkEft_B_L24				64,2496,128,128
#define Anime_NorAtkEft_C_L1				832,2688,128,128
#define Anime_NorAtkEft_C_L2				640,2688,128,128
#define Anime_NorAtkEft_C_L3				448,2688,128,128
#define Anime_NorAtkEft_C_L4				256,2688,128,128
#define Anime_NorAtkEft_C_L5				64,2688,128,128
#define Anime_NorAtkEft_C_L6				832,2880,128,128
#define Anime_NorAtkEft_C_L7				640,2880,128,128
#define Anime_NorAtkEft_C_L8				448,2880,128,128
#define Anime_NorAtkEft_C_L9				256,2880,128,128
#define Anime_NorAtkEft_C_L10				64,2880,128,128
#define Anime_NorAtkEft_C_L11				832,3072,128,128
#define Anime_NorAtkEft_C_L12				640,3072,128,128
#define Anime_NorAtkEft_C_L13				448,3072,128,128
#define Anime_NorAtkEft_C_L14				256,3072,128,128
#define Anime_NorAtkEft_C_L15				64,3072,128,128
#define Anime_NorAtkEft_C_L16				832,3264,128,128
#define Anime_NorAtkEft_C_L17				640,3264,128,128
#define Anime_NorAtkEft_C_L18				448,3264,128,128
#define Anime_NorAtkEft_C_L19				256,3264,128,128
#define Anime_NorAtkEft_C_L20				64,3264,128,128
#define Anime_NorAtkEft_C_L21				832,3456,128,128
#define Anime_NorAtkEft_C_L22				640,3456,128,128
#define Anime_NorAtkEft_C_L23				448,3456,128,128
#define Anime_NorAtkEft_C_L24				256,3456,128,128

#define Anime_RemDeathPara_R1				0,0,128,128
#define Anime_RemDeathPara_R2				179,0,128,128
#define Anime_RemDeathPara_R3				0,143,128,128
#define Anime_RemDeathPara_R4				191,143,128,128
#define Anime_RemDeathPara_R5				384,143,128,128
#define Anime_RemDeathPara_L1				448,0,128,128
#define Anime_RemDeathPara_L2				268,0,128,128
#define Anime_RemDeathPara_L3				448,143,128,128
#define Anime_RemDeathPara_L4				257,143,128,128
#define Anime_RemDeathPara_L5				64,143,128,128
#define Anime_RemDeathOffset_Y				10

#define Anime_RemBeatenPara_L1				640,0,128,128
#define Anime_RemBeatenPara_L2				449,0,128,128
#define Anime_RemBeatenPara_L3				259,0,128,128
#define Anime_RemBeatenPara_L4				66,0,128,128
#define Anime_RemBeatenPara_R1				0,0,128,128
#define Anime_RemBeatenPara_R2				192,0,128,128
#define Anime_RemBeatenPara_R3				383,0,128,128
#define Anime_RemBeatenPara_R4				575,0,128,128
#define Anime_RemBeatOffset_LX				32
#define Anime_RemBeatOffset_RX				10
#define Anime_RemBeatOffset_Y				20

#define Anime_RemSkillEffect_1				0,576,128,128
#define Anime_RemSkillEffect_2				192,576,128,128
#define Anime_RemSkillEffect_3				384,576,128,128
#define Anime_RemSkillEffect_4				576,576,128,128
#define Anime_RemSkillEffect_5				768,576,128,128
#define Anime_RemSkillEffect_6				0,768,128,128
#define Anime_RemSkillEffect_7				192,768,128,128
#define Anime_RemSkillEffect_8				384,768,128,128
#define Anime_RemSkillEffect_9				576,768,128,128

#define Anime_Barrage_HitEft_S1				240,45,128,128
#define Anime_Barrage_HitEft_S2				432,45,128,128
#define Anime_Barrage_HitEft_S3				624,45,128,128
#define Anime_Barrage_HitEft_S4				816,45,128,128
#define Anime_Barrage_HitEft_S5				48,237,128,128
#define Anime_Barrage_HitEft_S6				240,237,128,128
#define Anime_Barrage_HitEft_S7				432,237,128,128
#define Anime_Barrage_HitEft_S8				624,237,128,128

#define Anime_Laser_HitEft_1				416,54,128,128
#define Anime_Laser_HitEft_2				608,54,128,128
#define Anime_Laser_HitEft_3				800,54,128,128
#define Anime_Laser_HitEft_4				32,246,128,128
#define Anime_Laser_HitEft_5				224,246,128,128
#define Anime_Laser_HitEft_6				416,246,128,128
#define Anime_Laser_HitEft_7				608,246,128,128
#define Anime_Laser_HitEft_8				800,246,128,128
#define Anime_Laser_HitEft_9				32,438,128,128
#define Anime_Laser_HitEft_10				224,438,128,128
#define Anime_Laser_HitEft_11				416,438,128,128
#define Anime_Laser_HitEft_12				608,438,128,128

#define Anime_RemSkillActionPara_1			1,28,107,95
#define Anime_RemSkillActionPara_2			191,28,108,95
#define Anime_RemSkillActionPara_3			383,22,97,101
#define Anime_RemSkillActionPara_4			575,16,94,107
#define Anime_RemSkillActionPara_5			767,14,94,109
#define Anime_RemSkillActionPara_6			5,196,91,119
#define Anime_RemSkillActionPara_7			244,191,119,135
#define Anime_RemSkillActionPara_8			435,215,119,116
#define Anime_RemSkillActionPara_9			624,220,69,110
#define Anime_RemSkillActionPara_10			799,220,81,95
#define Anime_RemSkillActionPara_11			32,413,80,95
#define Anime_RemSkillActionPara_12			223,413,81,95
#define Anime_RemSkillActionPara_13			414,413,82,95
#define Anime_RemSkillActionPara_14			596,410,73,98
#define Anime_RemSkillActionPara_15			777,413,84,95

#define Anime_RemSkillB_HitEffect_1			417,30,128,128
#define Anime_RemSkillB_HitEffect_2			609,30,128,128
#define Anime_RemSkillB_HitEffect_3			801,30,128,128
#define Anime_RemSkillB_HitEffect_4			33,222,128,128
#define Anime_RemSkillB_HitEffect_5			225,222,128,128
#define Anime_RemSkillB_HitEffect_6			417,222,128,128
#define Anime_RemSkillB_HitEffect_7			609,222,128,128
#define Anime_RemSkillB_HitEffect_8			801,222,128,128
#define Anime_RemSkillB_HitEffect_9			33,414,128,128
#define Anime_RemSkillB_HitEffect_10		225,414,128,128
#define Anime_RemSkillB_HitEffect_11		417,414,128,128
#define Anime_RemSkillB_HitEffect_12		609,414,128,128
#define Anime_RemSkillB_HitEffect_13		801,414,128,128
#define Anime_RemSkillB_HitEffect_14		33,606,128,128
#define Anime_RemSkillB_HitEffect_15		225,606,128,128
#define Anime_RemSkillB_HitEffect_16		417,606,128,128
#define Anime_RemSkillB_HitEffect_17		609,606,128,128
#define Anime_RemSkillB_HitEffect_18		801,606,128,128

//动画偏移量 
enum Anime_SkillOffset_R{
	Anime_SkillOffset_R1x = 37,
	Anime_SkillOffset_R1y = 2,
	Anime_SkillOffset_R2x = 39,
	Anime_SkillOffset_R2y = 2,
	Anime_SkillOffset_R3x = 39,
	Anime_SkillOffset_R3y = 6,
	Anime_SkillOffset_R4x = 39,
	Anime_SkillOffset_R4y = 12,
	Anime_SkillOffset_R5x = 39,
	Anime_SkillOffset_R5y = 14,
	Anime_SkillOffset_R6x = 33,
	Anime_SkillOffset_R6y = 24,
	Anime_SkillOffset_R7x = 3,
	Anime_SkillOffset_R7y = 29,
	Anime_SkillOffset_R8x = 4,
	Anime_SkillOffset_R8y = 5,
	Anime_SkillOffset_R9x = 7,
	Anime_SkillOffset_R9y = 0,
	Anime_SkillOffset_R10x = 24,
	Anime_SkillOffset_R10y = 0,
	Anime_SkillOffset_R11x = 23,
	Anime_SkillOffset_R11y = 0,
	Anime_SkillOffset_R12x = 24,
	Anime_SkillOffset_R12y = 0,
	Anime_SkillOffset_R13x = 25,
	Anime_SkillOffset_R13y = 0,
	Anime_SkillOffset_R14x = 17,
	Anime_SkillOffset_R14y = 3,
	Anime_SkillOffset_R15x = 27,
	Anime_SkillOffset_R15y = 0,
};
enum Anime_SkillOffset_L{
	Anime_SkillOffset_L1x = 19,
	Anime_SkillOffset_L1y = 0,
	Anime_SkillOffset_L2x = 18,
	Anime_SkillOffset_L2y = 0,
	Anime_SkillOffset_L3x = 8,
	Anime_SkillOffset_L3y = 6,
	Anime_SkillOffset_L4x = 4,
	Anime_SkillOffset_L4y = 12,
	Anime_SkillOffset_L5x = 3,
	Anime_SkillOffset_L5y = 14,
	Anime_SkillOffset_L6x = 6,
	Anime_SkillOffset_L6y = 24,
	Anime_SkillOffset_L7x = 64,
	Anime_SkillOffset_L7y = 29,
	Anime_SkillOffset_L8x = 64,
	Anime_SkillOffset_L8y = 5,
	Anime_SkillOffset_L9x = 13,
	Anime_SkillOffset_L9y = 0,
	Anime_SkillOffset_L10x = 7,
	Anime_SkillOffset_L10y = 0,
	Anime_SkillOffset_L11x = 7,
	Anime_SkillOffset_L11y = 0,
	Anime_SkillOffset_L12x = 7,
	Anime_SkillOffset_L12y = 0,
	Anime_SkillOffset_L13x = 6,
	Anime_SkillOffset_L13y = 0,
	Anime_SkillOffset_L14x = 6,
	Anime_SkillOffset_L14y = 3,
	Anime_SkillOffset_L15x = 8,
	Anime_SkillOffset_L15y = 0,
};

/************结构体声明************/
//玩家参数结构体 
typedef struct Player_Parameter
{
	int x;
	int y;
	int Length;
	int Width;
	float HP;
	int MP;
	int BeatenBoss_Spd;
	char Defense;
	char BeatenBossBarrage_Ctr;
	char BeatenBossLaser_Ctr;
	char BeatenBossTentacle_Ctr;
	char Flag_NorAtk;
	bool Flag_Skilling_A;
	bool Flag_Skilling_B;
	bool Flag_Barrage;
	bool Flag_Beaten;
	bool Flag_Death;
	bool Flag_Jump;
	bool Flag_Direction;
}Player_Parameter;
 
//对象参数结构体（技能、方块） 
typedef struct Object_Parameter
{
	int page;
	int x;
	int y;
	int Length;
	int Width;
	int type;
	int Damage;			//伤害标识，为正时对敌伤害，为负时敌对伤害，数值表示伤害值 
	bool Flag_Direction;
}Object_Parameter;

//敌对单位结构体 
typedef struct Enemy_Parameter
{
	int page;
	int x;
	int y;
	int Length;
	int Width;
	int type;
	int Damage;
	int HP;
	int alpha;
	int Attack_Ctr;
	int JumpHeight_Ctr;
	int FallHeight_Ctr;
	int JumpStart_Loc;
	char JumpAnime_Ctr;
	char AnimeAttack_Ctr;
	char DeathEffect_Ctr;
	char Flag_HitEffect;
	char HitEffect_Ctr;
	bool Flag_Attack;
	bool Flag_Death;	//为1时死亡
	bool Flag_Direction;
}Enemy_Parameter;

//BOSS单位结构体
typedef struct Boss_Parameter
{
	int page;
	int x;
	int y;
	int Length;
	int Width;
	int type;
	int HP;
	int Target_Y;
	int AtkCD_Ctr;
	char SkillSelect;
	char BarrageType;
	char Direction;
	char AnimeAcitve_Ctr;
	char MoveSpeed_Ctr;
	char DeathEffect_Ctr;
	char DeathEftSpeed_Ctr;
	char Flag_HitEffect;
	char HitEffect_Ctr;
	bool Flag_Death;
	bool isSilling;
}Boss_Parameter;

//弹幕结构体 
typedef struct Barrage_Parameter
{
	int x;
	int y;
	int rad;
	char type;
	bool flag;
	float arc;
}Barrage_Parameter;

//BOSS触手攻击结构体 
typedef struct Tentacle_Parameter
{
	float x;
	int y;
	int damage;
	bool direction;
	bool atkflag;
	bool musicflag;
}Tentacle_Parameter;

typedef struct MOUSE
{
	int x;
	int y;
	int wheel;
	bool is_left;
	bool is_wheel;
}MOUSE;
/*************变量声明*************/
unsigned int DebugTestPoint;
FILE* stream;
mouse_msg Temp_Mouse = {0};
MOUSE Mouse = {0};
//图形变量声明 
PIMAGE Layer_Background;	//include blocks 
PIMAGE IMG_Background_A;
PIMAGE IMG_Background_B;
PIMAGE IMG_Gameover;
PIMAGE IMG_Block;
PIMAGE IMG_Remilia_Move_L[9];
PIMAGE IMG_Remilia_Move_R[8];
PIMAGE IMG_Remilia_Stand_L[8];
PIMAGE IMG_Remilia_Stand_R[8];
PIMAGE IMG_Rem_NorAtkAct_R;
PIMAGE IMG_Rem_NorAtkAct_L;
PIMAGE IMG_Defense_R[2];
PIMAGE IMG_Defense_L[2];
PIMAGE IMG_Remilia_SkillStart_BL[25];
PIMAGE IMG_Remilia_SkillStart_BR[25];
PIMAGE IMG_Remilia_SkillArrow_BL[20];
PIMAGE IMG_Remilia_SkillArrow_BR[20];
PIMAGE IMG_RemSkillB_HitEffect;
PIMAGE IMG_BarrageHitEffect;
PIMAGE IMG_LaserHitEffect;
PIMAGE IMG_Enemy_Cerulean_Blue_L[14];
PIMAGE IMG_Enemy_Cerulean_Blue_R[14];
PIMAGE IMG_Enemy_Cerulean_Pink[14];
PIMAGE IMG_Enemy_CerBlue_Death[17];
PIMAGE IMG_Enemy_CerPink_Death[17];
PIMAGE IMG_Enemy_Attack_Normal_L[8];
PIMAGE IMG_Enemy_Attack_Normal_R[8];
PIMAGE IMG_Boss[20]; 
PIMAGE IMG_BossTentacle;
PIMAGE IMG_BossBarrage;
PIMAGE IMG_BossLaser[29];
PIMAGE IMG_BossRing[29];
PIMAGE IMG_BossDeath[26];
PIMAGE IMG_Remilia_Start[20];
PIMAGE IMG_Remilia_Skill_AL;
PIMAGE IMG_Remilia_Skill_AR;
PIMAGE IMG_Remilia_Death_L;
PIMAGE IMG_Remilia_Death_R;
PIMAGE IMG_Remilia_Beaten_L;
PIMAGE IMG_Remilia_Beaten_R;
PIMAGE IMG_Remilia_Barrage[7];
PIMAGE IMG_Remilia_BarrageAct[3];
PIMAGE IMG_Buttonselected;
PIMAGE IMG_ButtonUnselected;
PIMAGE IMG_PublicImage;
PIMAGE IMG_HPMPBar;
PIMAGE IMG_BossHPMPBar_1;
PIMAGE IMG_BossHPMPBar_2;
PIMAGE IMG_Reply_Props[12];
PIMAGE IMG_Reply_Eft[9];
PIMAGE IMG_Beaten_Tentacle[7];
//音乐变量声明
MUSIC Music_LOGO;
MUSIC Music_BattleBGM;
MUSIC Music_BossBGM;
MUSIC Music_StartBGM;
MUSIC Music_GameOver;
MUSIC Music_GameVictory;
MUSIC Music_RemiliaDeath;
MUSIC Music_RemSkill_A;
MUSIC Music_RemSkill_B_Start;
MUSIC Music_RemSkill_B_Flying;
MUSIC Music_CerBlueAttN;
MUSIC Music_GUISelected_1;
MUSIC Music_GUIConfirm_1;
MUSIC Music_Beaten[3];
MUSIC Music_NorAtk[3];
MUSIC Music_PinkJump;
MUSIC Music_BossBarrageFire;
MUSIC Music_BossBarrageHit;
MUSIC Music_BossLaser;
MUSIC Music_HPreply; 
MUSIC Music_Blood;
MUSIC Music_Tentacle;
MUSIC Music_RemBarrage;
//结构体变量声明 
Player_Parameter Remilia = {0};
Object_Parameter Remilia_NorAtk_A = {0};
Object_Parameter Remilia_NorAtk_B = {0};
Object_Parameter Remilia_NorAtk_C = {0};
Object_Parameter Remilia_Skill_A = {0};
Object_Parameter Remilia_Skill_B = {0};
Object_Parameter **MapData_Block;
Enemy_Parameter  **MapData_Enemy;
Boss_Parameter Boss = {0};
Barrage_Parameter BossBarrage_1[BossAtk_Barrage_Density] = {0};
Barrage_Parameter BossBarrage_2[BossAtk_Barrage_Density] = {0};
Barrage_Parameter RemBarrage_1[SkillBarrage_Density] = {0};
Barrage_Parameter RemBarrage_2[SkillBarrage_Density] = {0};
Tentacle_Parameter BossTentacle[BossAtk_Tentacle_Amount] = {0};

//系统变量
int *Page_BlockAmount;
int *Page_BorderLine;
int (*Page_EnemyTypeAmount)[4];		//统计每种类型敌人的数量 [0]总数[1]type10数量[2]type11数量[3]type12数量 
int System_DelayTime = System_RefreshRate;
int Page_Amount = 0;
int Window_TotalLength = 0;
int Current_Page = 0;
int CurrentScreen_Xaxis = 0;
int BeatMusRand = 0;
int MPRestore_Ctr = 0;
bool Background_ReverseFlag = 1;
bool ScreenShiftDirection = 1;
//运动变量 
int Move_Jumped_Height = 0;
int Move_Jump_StartHeight = 0;
int JumpDelay = 0;
bool Flag_isMoving = 0;
bool DefenseFlag = 0;
int DefenseCtr = 0;
//玩家动画处理变量 
int Anime_Offset_x=Remilia_initX;
int Anime_Offset_y=Remilia_initY;
int Anime_MoveStand_FlagA = 1;
int Anime_MoveStand_FlagB = 0;
int Anime_BeatenCtrA = 1;
int Anime_BeatenCtrB = 0;
//普通攻击处理变量
int NorAtk_CDcounter = 0; 
int NorAtk_CtrA = 1;
int NorAtk_CtrB = 0;
int NorAtkEft_CtrA = 1;
int NorAtkEft_CtrB = 0;
int NorAtk_TypeCtr = 0;
char NorAtk_Type = 1;
char NorAtk_EftStart = 0;
//技能A处理变量 
int SkillA_CDcounter = 0;
bool Flag_isSkilling = 0;	//技能进行中标志 
int Anime_SkillA_FlagA = 1;
int Anime_SkillA_FlagB = 0;
//技能B处理变量 
int SkillB_CDcounter = 0;
int Anime_SkillB_FlagA = 0;
int Anime_SkillB_FlagB = 0;
int Anime_SkillBArrow_FlagA = 0;
int Anime_SkillBArrow_FlagB = 0;
int Anime_SkillBHitEffect_Flag = 0;
int Flag_SkillB_CD = 0;
bool Flag_SkillArrow_B = 0;
//大招处理变量
int Barrage_Height = SkillBarrage_Height;
int Barrage_CDcounter = 0; 
int Barrage_Speed_Ctr = 0;
int Barrage_ActCtr = 0;
int Barrage_Ctr_A = 0;
int Barrage_Ctr_B = 0;
int Barrage_Flag = -1;
//天蓝怪处理变量 
int Anime_CeruBlue_CtrA = 0;
int Anime_CeruBlue_CtrB = 0;
int Anime_CeruPink_CtrA = 0;
int Anime_CeruPink_CtrB = 0;
int Anime_CerBlue_DeathFlag = 0;
int Enemy_CeruleanBlue_Flag = 0;
int Enemy_CerBlue_AttCtr = 0;
//Boss处理变量 
int BossStage_Xlocation	= 0;
int AnimeAcitve_SPCtr = 0;
bool isBossStage = 0;

char BossAtk_Barrage_Flag = -1;
int BossAtk_Ctr_A = 0;
int BossAtk_Ctr_B = 0;
int BossAtk_SpeedCtr = 0;
//其它
int Props_ReplyHP_Ctr = 0; 
int Props_ReplyDeath_Ctr = 0;
bool Check_EnemyDamageNormal = 0;
bool Flag_GUIMusStu = 0;
bool Flag_GUIPicStu = 0;
char String[10];

/*************函数声明*************/
//系统函数 
bool SYS_MapFile_Read(int);
void SYS_Graphics_Init(void);
void SYS_Anime_Init(void);
void SYS_Image_Init(void);
void SYS_debug(void);
void SYS_Block_Set(Object_Parameter,int,int,int,int,int);
void SYS_Player_Init(void);
void SYS_Music_Init(void);
bool SYS_Game_Over(void);
void SYS_Parameter_Init(void);
void SYS_GetMouse(void);
void SYS_Speed(void);
//检测函数 
long long Check_Collision(int);
long long Check_Accessible(int);
int Check_BelowBlock(int,int);
int Check_TopBlock(int,int);
int Check_LeftBlock(int,int);
int Check_RightBlock(int,int);
//玩家动画 
void Anime_PlayerMove(bool);
void Anime_PlayerMoveR(void);
void Anime_PlayerMoveL(void);
void Anime_PlayerStand(bool);
void Anime_RemiliaStand_R(void);
void Anime_RemiliaStand_L(void);
void Anime_PlayerDeath(void);
void Anime_PlayerDeathR(void);
void Anime_PlayerDeathL(void);
void Anime_RemBeaten(bool);
void Anime_RemBeaten_L(void);
void Anime_RemBeaten_R(void);
void Anime_PlayerDefense(bool);
void Anime_PlayerDefense_L(void);
void Anime_PlayerDefense_R(void);
void Anime_RemBeatenBarrage(void);
void Anime_RemBeatenLaser(void);
void Anime_RemBeatenTentacle(void);
//玩家大招
void Process_BarrageDamage(int page,Barrage_Parameter*, Barrage_Parameter*);
void Process_BarrageDamageBoss(Barrage_Parameter*, Barrage_Parameter*);
void Player_BarrageDamage(Barrage_Parameter*, Barrage_Parameter*);
void Process_Remilia_Barrage(void); 
void RemiliaSkill_Barrage(void);
void RemiliaSkill_Barrage_Init(void);
//玩家普通攻击
void Anime_RemNorAtk(bool Direction);
void Anime_RemNorAtk_AR(void);
void Anime_RemNorAtk_BR(void); 
void Anime_RemNorAtk_CR(void);
void Anime_RemNorAtk_AL(void);
void Anime_RemNorAtk_BL(void); 
void Anime_RemNorAtk_CL(void); 
void Anime_RemNorEft(bool Direction);
void Anime_RemNorEft_AR(void);
void Anime_RemNorEft_BR(void);
void Anime_RemNorEft_CR(void);
void Anime_RemNorEft_AL(void);
void Anime_RemNorEft_BL(void);
void Anime_RemNorEft_CL(void);
//玩家技能A
void Anime_RemiliaSkill_A(bool);
void Anime_RemSkill_HitEffect(void);
void Anime_RemiliaSkill_AR(void);
void Anime_RemiliaSkill_AL(void);
//玩家技能B
void Anime_RemiliaSkill_B(bool);
void Anime_RemiliaSkill_BR(void);
void Anime_RemiliaSkill_BL(void);
void Anime_RemSkillBArrow(bool);
void Anime_RemSkillBArrow_R(void);
void Anime_RemSkillBArrow_L(void);
//敌对生物
long long EnemyCheck_Collision(int,int,int);
long long EnemyCheck_Accessible(int,int,int);
void Enemy_Damage_Normal(void);
void Enemy_Cerulean_Blue(void); 
void Enemy_Cerulean_Pink(void); 
void Process_Cerulean_Blue(int);
void Process_Cerulean_Pink(int);
//Boss
bool BossStage(void);
void Process_Boss(void);
void Anime_BossActive(void);
void BossAtk_Barrage(void);
void BossAtk_BarrageInit_Type1(void);
void BossAtk_BarrageInit_Type2(void);
void BossAtk_BarrageInit_Type3(void);
void BossAtk_BarrageInit_Type4(void);
void BossAtk_Laser(void);
void BossAtk_Tentacle(void);
bool Anime_Boss_DeathEft(void);
//玩家控制函数 
void Process_PlayerMoveRight(void);
void Process_PlayerMoveLeft(void);
void Process_PlayerStartJump(void);
void Process_PlayerJumpingUp(void);
void Process_PlayerDropDown(void);
void Process_PlayerSkill(void);
void Process_PlayerDefense(void);
//屏幕控制函数 
void Graphics_R_Shift(void);
void Graphics_L_Shift(void);
void Graphics_AuxiliaryGrid(int);
//GUI
bool Check_MouseLocation(int,int,int,int);
void GUI_GameStart(void);
void GUI_GameOver(void);
void GUI_GameVictory(void);
void GUI_HpMp_bar(void);
//其它 
void Frame_Object(Object_Parameter);
void Frame_Player(Player_Parameter);
void Frame_Enemy(Enemy_Parameter);
void Frame_Boss(Boss_Parameter);

void Process_SkillCD_MPRestore(void);
void Process_PlayerDamage(int,Object_Parameter);
void Process_PDamageBoss(Object_Parameter);
void Process_RemSkill_HitEffect(void);
void Player_SkillDamage(Object_Parameter); 
void Anime_RemSkill_HitBoss(void);
void Anime_RemSkill_HitEffect(int page);

int Math_Acceleration(int);
double Math_RotateAngle(int,int,int,int);
void Math_RotateAxis(Barrage_Parameter*,bool);
void Debug_BinOutput(long long);

void Process_reply_props(int);
void Props_Replay_HP(void);


/************************************/
/*函数名： main 					*/
/*功  能： 主函数			 		*/
/*参  数： 		 					*/
/*返回值： 		 					*/
/************************************/
int main()
{
	SYS_Graphics_Init();
	SYS_Anime_Init();
	
	#ifdef ENABLE_DebugMode
		SYS_debug();
	#else
	
	SYS_Player_Init();
	SYS_Music_Init();
	GUI_GameStart();
	
	while(is_run())
	{
		SYS_GetMouse();
		
		if(Music_BattleBGM.GetPlayStatus() == MUSIC_MODE_STOP)
			Music_BattleBGM.Play(0);
			
		if(keystate(VK_ESCAPE))
			exit(0);//退出游戏 
				
		randomize();//随机数重置 
		
		Process_SkillCD_MPRestore();
		
		SYS_Speed();
		
		if(!Flag_isSkilling)
		{
			if(!Remilia.Defense)
			{
				//控制处理 
				Process_PlayerSkill();
				Process_PlayerMoveRight();
				Process_PlayerMoveLeft();
				Process_PlayerJumpingUp();
				//动画处理 
				Anime_PlayerStand(Remilia.Flag_Direction);
				Anime_PlayerMove(Remilia.Flag_Direction);
				Anime_RemBeaten(Remilia.Flag_Direction);
			}
			else
			{
				Anime_PlayerDefense(Remilia.Flag_Direction);
			}
			Process_PlayerDefense();
		}
		else if(Flag_isSkilling)
		{
			//技能A释放 
			Anime_RemiliaSkill_A(Remilia.Flag_Direction);
			//技能B释放 
			Anime_RemiliaSkill_B(Remilia.Flag_Direction);
			//普通攻击 
			Anime_RemNorAtk(Remilia.Flag_Direction);
			//大招
			Process_Remilia_Barrage();
		}
		if(!Remilia.Flag_Barrage)
			Process_PlayerDropDown();
		//技能B投射物飞行 
		Anime_RemSkillBArrow(Remilia_Skill_B.Flag_Direction);
		//天蓝怪动画 
		Enemy_Cerulean_Blue();
		Enemy_Cerulean_Pink();
		//道具处理
		Props_Replay_HP();
		//伤害处理 
		Enemy_Damage_Normal();
		//处理被攻击效果 
		Process_RemSkill_HitEffect();
		//普通攻击效果 
		Anime_RemNorEft(Remilia.Flag_Direction);
		//血条绘制 
		GUI_HpMp_bar();
		//更新显示 
		delay_fps(System_DelayTime);
		//清屏 
		putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
 
		if(CurrentScreen_Xaxis == BossStage_Xlocation)
		{
			isBossStage = 1;
			BossStage();
		}
		
		if(Remilia.y>=WindowSize_H || Remilia.HP<=0)
		{
			SYS_Game_Over();
		}
	}
	#endif
	return(0);
}

/************************************/
/*函数名： SYS_MapFile_Read			*/
/*功  能：读取地图文件			 	*/
/*参  数：关卡数		 			*/
/*返回值：错误代码	 		 		*/
/************************************/
bool SYS_MapFile_Read(int stage)
{
	int i=0,j=0,n=0;
 
	stream = fopen("Data\\system","r");
	if(stream != NULL)
	{
		fscanf(stream,"%d",&System_DelayTime);
		fclose(stream);
	}
	else
	{
		System_DelayTime = 1000;
	}
 
	switch(stage)
	{
		case 1:stream = fopen("Data\\Stage1.map","r");break;
		default:printf("ILLEGAL STAGE!\n");return(0);
	}
	//读取页数 
	fscanf(stream,"%d",&Page_Amount);
	Window_TotalLength = Page_Amount*WindowSize_L;	//计算页面总长度 
	
	//根据页数分配空间 
	MapData_Block = new Object_Parameter*[Page_Amount];	//方块指针数组 
	MapData_Enemy = new Enemy_Parameter*[Page_Amount];	//敌人指针数组 
	Page_EnemyTypeAmount = new int[Page_Amount][4];	//每页每种敌人数量
	Page_BorderLine = new int[Page_Amount];
	Page_BlockAmount = new int[Page_Amount];//每页的方块数量 
	
	//写入页分界线位置 
	for(i=0;i<Page_Amount;i++)
	{
		Page_BorderLine[i] = (i+1)*WindowSize_L-1;
	}
	
	//读取每页的方块数目 
	for(i=0;i<Page_Amount;i++)
	{
		fscanf(stream,"%d",&Page_BlockAmount[i]);
	}
	
	//根据每页的方块数目分配空间 
	for(i=0;i<Page_Amount;i++)
	{
		if(Page_BlockAmount[i]!=0)
		{
			MapData_Block[i] = new Object_Parameter[Page_BlockAmount[i]];
		}
		else
		{
			MapData_Block[i] = NULL;
		}
	}
	
	ProgressBar(70);
	
	//读入方块数据 
	for(i=0;i<Page_Amount;i++)
	{
		for(j=0;j<Page_BlockAmount[i];j++)
		{
			n=fscanf(stream,"%d,%d,%d,%d,%d,%d,%d",&MapData_Block[i][j].page,&MapData_Block[i][j].x,&MapData_Block[i][j].y,&MapData_Block[i][j].Length,&MapData_Block[i][j].Width,&MapData_Block[i][j].type,&MapData_Block[i][j].Damage);
			#ifdef ENABLE_ExpandAxis_Mode
			MapData_Block[i][j].x += MapData_Block[i][j].page*WindowSize_L;
			#endif
			if(n!=7)
			{
				printf("\nREAD FILE ERROR!\n");
				return(0);
			}
			MapData_Block[i][j].Flag_Direction = 0;
		}
	}
	
	ProgressBar(170);
	
	//读取每页的敌人数目
	for(i=0;i<Page_Amount;i++)
	{
		fscanf(stream,"%d",&Page_EnemyTypeAmount[i][0]);
		Page_EnemyTypeAmount[i][1]=0;
		Page_EnemyTypeAmount[i][2]=0;
		Page_EnemyTypeAmount[i][3]=0;
	}
	
	//根据每页的敌人数目分配空间 
	for(i=0;i<Page_Amount;i++)
	{
		if(Page_EnemyTypeAmount[i][0]!=0)
		{
			MapData_Enemy[i] = new Enemy_Parameter[Page_EnemyTypeAmount[i][0]];
		}	
		else
		{
			MapData_Enemy[i] = NULL;
		}
	}
	
	//读入敌人数据 
	for(i=0;i<Page_Amount;i++)
	{
		for(j=0;j<Page_EnemyTypeAmount[i][0];j++)
		{
			n=fscanf(stream,"%d,%d,%d,%d,%d,%d,%d",&MapData_Enemy[i][j].page,&MapData_Enemy[i][j].x,&MapData_Enemy[i][j].y,&MapData_Enemy[i][j].Length,&MapData_Enemy[i][j].Width,&MapData_Enemy[i][j].type,&MapData_Enemy[i][j].Damage);
			#ifdef ENABLE_ExpandAxis_Mode
			MapData_Enemy[i][j].x += MapData_Enemy[i][j].page*WindowSize_L;
			#endif
			if(n!=7)
			{
				printf("\nREAD FILE ERROR!\n");
				return(0);
			}
			randomize();
			//统计当前页每种敌人的数量 
			if(MapData_Enemy[i][j].type == Enemy_CeruleanBlue_Number)
			{
				Page_EnemyTypeAmount[i][1]++;
				MapData_Enemy[i][j].HP = Enemy_CeruleanBlue_Life;
				MapData_Enemy[i][j].Damage = random(100)-50+Enemy_CeruleanBlue_Damage;
			}
				
			if(MapData_Enemy[i][j].type == Enemy_CeruleanPink_Number)
			{
				Page_EnemyTypeAmount[i][2]++;
				MapData_Enemy[i][j].HP = Enemy_CeruleanPink_Life;
				MapData_Enemy[i][j].Damage = random(100)-50+Enemy_CeruleanPink_Damage;
				MapData_Enemy[i][j].Length = 62;
			}
				
			if(MapData_Enemy[i][j].type == 12)
			{
				Page_EnemyTypeAmount[i][3]++;
				MapData_Enemy[i][j].HP = 1;
				MapData_Enemy[i][j].Damage = random(100)+Props_ReplyHp_Value;
			}
				
			MapData_Enemy[i][j].alpha = 0xFF;
			MapData_Enemy[i][j].Flag_Death = 0;
			MapData_Enemy[i][j].Flag_Direction = 0;
			MapData_Enemy[i][j].Flag_HitEffect = 0;
			MapData_Enemy[i][j].HitEffect_Ctr = 1;
			MapData_Enemy[i][j].DeathEffect_Ctr = -1;
			MapData_Enemy[i][j].Attack_Ctr = 0;
			MapData_Enemy[i][j].Flag_Attack = 0;
			MapData_Enemy[i][j].AnimeAttack_Ctr = -1;
			MapData_Enemy[i][j].JumpStart_Loc = MapData_Enemy[i][j].y;
			MapData_Enemy[i][j].JumpHeight_Ctr = 0;
			MapData_Enemy[i][j].FallHeight_Ctr = 0;
			MapData_Enemy[i][j].JumpAnime_Ctr = 0;
		}
	}
	
	ProgressBar(250);
	
	fclose(stream);
	return(1);
}

/************************************/
/*函数名： SYS_Graphics_Init		*/
/*功  能： 图形系统初始化		 	*/
/*参  数： 		 					*/
/*返回值： 		 					*/
/************************************/
void SYS_Graphics_Init(void)
{
	int i;
	
	setinitmode( INIT_ANIMATION );
	initgraph(WindowSize_L,WindowSize_H);
	setcaption("Touhou Japari 1.1.9");
	setcolor(WHITE);
	setbkcolor(WHITE);
	setfillcolor(EGERGB(46,79,144));
	setbkmode(TRANSPARENT);
	
	#ifdef ENABLE_Music
	Music_LOGO.OpenFile("Music\\LOGO.mp3");
	Music_LOGO.SetVolume(0.6f);
	Music_LOGO.Play(0);
	#endif
	
	IMG_PublicImage	= newimage();
	getimage(IMG_PublicImage,"ScenesImage\\Menu\\Start\\LOGO_Brick.png");
	
	for(i=0;i<60;i++)
	{
		putimage_rotate(NULL,IMG_PublicImage,200,30,0.0f,0.0f,0.0f,1,i);
		delay_fps(45);
	}
	
	ProgressBar(20);
}

/************************************/
/*函数名： SYS_Anime_Init			*/
/*功  能： 动画系统初始化		 	*/
/*参  数： 		 					*/
/*返回值： 		 					*/
/************************************/
void SYS_Anime_Init(void)
{
	int i=0,j=0,k=0,block_i=0,block_j=0;
	
	SYS_MapFile_Read(1);
	SYS_Image_Init();
	
	//初始化背景 
	getimage(Layer_Background,0,0,Window_TotalLength,WindowSize_H);
	
	for(i=0;i<=Window_TotalLength;i+=3200)
	{
		if(Background_ReverseFlag)
		putimage(Layer_Background,i,0,3200,WindowSize_H,IMG_Background_A,0,0,3200,540);
		else
		putimage(Layer_Background,i,0,3200,WindowSize_H,IMG_Background_B,0,0,3200,540);
		
		Background_ReverseFlag = !Background_ReverseFlag;
	}
	ProgressBar(950);
	//初始化障碍物
	for(i=0;i<Page_Amount;i++)
	{
		for(j=0;j<Page_BlockAmount[i];j++)
		{
			switch(MapData_Block[i][j].type)
			{
				case 0:
					getimage_pngfile(IMG_Block,"ScenesImage\\block_img0.png");break;
				case 1:
					getimage_pngfile(IMG_Block,"ScenesImage\\block_img1.png");break;
				case 2:
					getimage_pngfile(IMG_Block,"ScenesImage\\block_img2.png");break;
				case 3:
					getimage_pngfile(IMG_Block,"ScenesImage\\block_img3.png");break;
				case 4:
					getimage_pngfile(IMG_Block,"ScenesImage\\block_img4.png");break;
				case 5:
					getimage_pngfile(IMG_Block,"ScenesImage\\block_img5.png");break;
				case 6:
					getimage_pngfile(IMG_Block,"ScenesImage\\block_img6.png");break;
				case 7:
					getimage_pngfile(IMG_Block,"ScenesImage\\block_img7.png");break;
				case 8:
					getimage_pngfile(IMG_Block,"ScenesImage\\block_img8.png");break;
				case 9:
					getimage_pngfile(IMG_Block,"ScenesImage\\block_img9.png");break;
				default:printf("BLOCK INITIALIZATION ERROR!");
			}
			
			//障碍物合并处理 (X轴)
			for(block_i=0;block_i<MapData_Block[i][j].Length;block_i+=60)
				putimage_withalpha(Layer_Background,IMG_Block,MapData_Block[i][j].x+block_i,MapData_Block[i][j].y);
		}
	}
	ProgressBar(1020);
	BossStage_Xlocation = Window_TotalLength - WindowSize_L;
	//释放图层
	putimage(NULL,0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
}

/************************************/
/*函数名： SYS_Image_Init			*/
/*功  能： 图形变量初始化		 	*/
/*参  数： 		 					*/
/*返回值： 		 					*/
/************************************/
void SYS_Image_Init(void)
{
	int i;
	
	for(i=0;i<3;i++)
	{
		IMG_Remilia_BarrageAct[i] = newimage();
	}
	for(i=0;i<7;i++)
	{
		IMG_Beaten_Tentacle[i] = newimage();
		IMG_Remilia_Barrage[i] = newimage();
	}
	for(i=0;i<8;i++)
	{
		IMG_Remilia_Move_R[i] = newimage();
		IMG_Remilia_Stand_L[i] = newimage();
		IMG_Remilia_Stand_R[i] = newimage();
		IMG_Enemy_Attack_Normal_L[i] = newimage();
		IMG_Enemy_Attack_Normal_R[i] = newimage();
	}
	for(i=0;i<9;i++)
	{
		IMG_Remilia_Move_L[i] = newimage();
		IMG_Reply_Eft[i] = newimage();
	}
	for(i=0;i<12;i++)
	{
		IMG_Reply_Props[i] = newimage();
	}
	for(i=0;i<14;i++)
	{
		IMG_Enemy_Cerulean_Pink[i] = newimage();
		IMG_Enemy_Cerulean_Blue_L[i] = newimage();
		IMG_Enemy_Cerulean_Blue_R[i] = newimage();
	}
	for(i=0;i<17;i++)
	{
		IMG_Enemy_CerPink_Death[i] = newimage();
		IMG_Enemy_CerBlue_Death[i] = newimage();
	}
	for(i=0;i<20;i++)
	{
		IMG_Remilia_SkillArrow_BL[i] = newimage();
		IMG_Remilia_SkillArrow_BR[i] = newimage();
		IMG_Remilia_Start[i] = newimage();
		IMG_Boss[i] = newimage();
	}
	for(i=0;i<25;i++)
	{
		IMG_Remilia_SkillStart_BL[i] = newimage();
		IMG_Remilia_SkillStart_BR[i] = newimage();
	}
	for(i=0;i<26;i++)
	{
		IMG_BossDeath[i] = newimage();
	}
	for(i=0;i<29;i++)
	{
		IMG_BossLaser[i] = newimage();
		IMG_BossRing[i] = newimage();				
	}
	
	//初始化图形变量 
	Layer_Background		= newimage();
	IMG_Remilia_Death_L 	= newimage();
	IMG_Remilia_Death_R 	= newimage();
	IMG_Remilia_Beaten_L	= newimage();
	IMG_Remilia_Beaten_R	= newimage();
	IMG_Remilia_Skill_AL	= newimage();
	IMG_Remilia_Skill_AR	= newimage();
	IMG_Background_A 		= newimage();
	IMG_Background_B 		= newimage();
	IMG_Block 				= newimage();
 	IMG_Buttonselected 		= newimage();
 	IMG_ButtonUnselected 	= newimage();
 	IMG_RemSkillB_HitEffect = newimage();
 	IMG_Gameover 			= newimage();
 	IMG_HPMPBar				= newimage();
 	IMG_BossHPMPBar_1		= newimage();
    IMG_BossHPMPBar_2		= newimage();
 	IMG_Rem_NorAtkAct_R		= newimage();
 	IMG_Rem_NorAtkAct_L		= newimage();
 	IMG_Defense_R[0]		= newimage();
 	IMG_Defense_R[1]		= newimage();
 	IMG_Defense_L[0]		= newimage();
 	IMG_Defense_L[1]		= newimage();
 	IMG_BossBarrage			= newimage();
 	IMG_BarrageHitEffect	= newimage();
 	IMG_LaserHitEffect      = newimage();
 	IMG_BossTentacle		= newimage();
 	
 	ProgressBar(400);
 	
	//读入图片 
	getimage_pngfile(IMG_BossTentacle,"PlayerImage\\Enemy\\Boss\\Tentacle\\Tentacle.png");
	getimage_pngfile(IMG_BarrageHitEffect,"PlayerImage\\BarrageHitEffect_s.png");
	getimage_pngfile(IMG_LaserHitEffect,"PlayerImage\\LaserHitEffect.png");
	getimage_pngfile(IMG_BossBarrage,"PlayerImage\\Enemy\\Boss\\Barrage\\barrage.png");
	getimage_pngfile(IMG_Beaten_Tentacle[0],"PlayerImage\\Tentacle\\1.png");
	getimage_pngfile(IMG_Beaten_Tentacle[1],"PlayerImage\\Tentacle\\2.png");
	getimage_pngfile(IMG_Beaten_Tentacle[2],"PlayerImage\\Tentacle\\3.png");
	getimage_pngfile(IMG_Beaten_Tentacle[3],"PlayerImage\\Tentacle\\4.png");
	getimage_pngfile(IMG_Beaten_Tentacle[4],"PlayerImage\\Tentacle\\5.png");
	getimage_pngfile(IMG_Beaten_Tentacle[5],"PlayerImage\\Tentacle\\6.png");
	getimage_pngfile(IMG_Beaten_Tentacle[6],"PlayerImage\\Tentacle\\7.png");
	getimage_pngfile(IMG_BossDeath[0],"PlayerImage\\Enemy\\Boss\\death\\1.png");
	getimage_pngfile(IMG_BossDeath[1],"PlayerImage\\Enemy\\Boss\\death\\2.png");
	getimage_pngfile(IMG_BossDeath[2],"PlayerImage\\Enemy\\Boss\\death\\3.png");
	getimage_pngfile(IMG_BossDeath[3],"PlayerImage\\Enemy\\Boss\\death\\4.png");
	getimage_pngfile(IMG_BossDeath[4],"PlayerImage\\Enemy\\Boss\\death\\5.png");
	getimage_pngfile(IMG_BossDeath[5],"PlayerImage\\Enemy\\Boss\\death\\6.png");
	getimage_pngfile(IMG_BossDeath[6],"PlayerImage\\Enemy\\Boss\\death\\7.png");
	getimage_pngfile(IMG_BossDeath[7],"PlayerImage\\Enemy\\Boss\\death\\8.png");
	getimage_pngfile(IMG_BossDeath[8],"PlayerImage\\Enemy\\Boss\\death\\9.png");
	getimage_pngfile(IMG_BossDeath[9],"PlayerImage\\Enemy\\Boss\\death\\10.png");
	getimage_pngfile(IMG_BossDeath[10],"PlayerImage\\Enemy\\Boss\\death\\11.png");
	getimage_pngfile(IMG_BossDeath[11],"PlayerImage\\Enemy\\Boss\\death\\12.png");
	getimage_pngfile(IMG_BossDeath[12],"PlayerImage\\Enemy\\Boss\\death\\13.png");
	getimage_pngfile(IMG_BossDeath[13],"PlayerImage\\Enemy\\Boss\\death\\14.png");
	getimage_pngfile(IMG_BossDeath[14],"PlayerImage\\Enemy\\Boss\\death\\15.png");
	getimage_pngfile(IMG_BossDeath[15],"PlayerImage\\Enemy\\Boss\\death\\16.png");
	getimage_pngfile(IMG_BossDeath[16],"PlayerImage\\Enemy\\Boss\\death\\17.png");
	getimage_pngfile(IMG_BossDeath[17],"PlayerImage\\Enemy\\Boss\\death\\18.png");
	getimage_pngfile(IMG_BossDeath[18],"PlayerImage\\Enemy\\Boss\\death\\19.png");
	getimage_pngfile(IMG_BossDeath[19],"PlayerImage\\Enemy\\Boss\\death\\20.png");
	getimage_pngfile(IMG_BossDeath[20],"PlayerImage\\Enemy\\Boss\\death\\21.png");
	getimage_pngfile(IMG_BossDeath[21],"PlayerImage\\Enemy\\Boss\\death\\22.png");
	getimage_pngfile(IMG_BossDeath[22],"PlayerImage\\Enemy\\Boss\\death\\23.png");
	getimage_pngfile(IMG_BossDeath[23],"PlayerImage\\Enemy\\Boss\\death\\24.png");
	getimage_pngfile(IMG_BossDeath[24],"PlayerImage\\Enemy\\Boss\\death\\25.png");
	getimage_pngfile(IMG_BossDeath[25],"PlayerImage\\Enemy\\Boss\\death\\26.png");
	getimage_pngfile(IMG_BossLaser[0],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillstart1.png");
	getimage_pngfile(IMG_BossLaser[1],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillstart2.png");
	getimage_pngfile(IMG_BossLaser[2],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA01.png");
	getimage_pngfile(IMG_BossLaser[3],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA02.png");
	getimage_pngfile(IMG_BossLaser[4],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA03.png");
	getimage_pngfile(IMG_BossLaser[5],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA04.png");
	getimage_pngfile(IMG_BossLaser[6],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA05.png");
	getimage_pngfile(IMG_BossLaser[7],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA06.png");
	getimage_pngfile(IMG_BossLaser[8],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA07.png");
	getimage_pngfile(IMG_BossLaser[9],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA08.png");
	getimage_pngfile(IMG_BossLaser[10],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA09.png");
	getimage_pngfile(IMG_BossLaser[11],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA10.png");
	getimage_pngfile(IMG_BossLaser[12],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA11.png");
	getimage_pngfile(IMG_BossLaser[13],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA12.png");
	getimage_pngfile(IMG_BossLaser[14],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA13.png");
	getimage_pngfile(IMG_BossLaser[15],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA14.png");
	getimage_pngfile(IMG_BossLaser[16],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA15.png");
	getimage_pngfile(IMG_BossLaser[17],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA16.png");
	getimage_pngfile(IMG_BossLaser[18],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA17.png");
	getimage_pngfile(IMG_BossLaser[19],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA18.png");
	getimage_pngfile(IMG_BossLaser[20],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA19.png");
	getimage_pngfile(IMG_BossLaser[21],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA20.png");
	getimage_pngfile(IMG_BossLaser[22],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA21.png");
	getimage_pngfile(IMG_BossLaser[23],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA22.png");
	getimage_pngfile(IMG_BossLaser[24],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA23.png");
	getimage_pngfile(IMG_BossLaser[25],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA24.png");
	getimage_pngfile(IMG_BossLaser[26],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillA25.png");
	getimage_pngfile(IMG_BossLaser[27],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillend1.png");
	getimage_pngfile(IMG_BossLaser[28],"PlayerImage\\Enemy\\Boss\\Laser\\BossSkillend2.png");
	ProgressBar(450);
	getimage_pngfile(IMG_BossRing[0],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb000.png");
	getimage_pngfile(IMG_BossRing[1],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb001.png");
	getimage_pngfile(IMG_BossRing[2],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb002.png");
	getimage_pngfile(IMG_BossRing[3],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb003.png");
	getimage_pngfile(IMG_BossRing[4],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb004.png");
	getimage_pngfile(IMG_BossRing[5],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb005.png");
	getimage_pngfile(IMG_BossRing[6],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb006.png");
	getimage_pngfile(IMG_BossRing[7],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb007.png");
	getimage_pngfile(IMG_BossRing[8],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb008.png");
	getimage_pngfile(IMG_BossRing[9],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb009.png");
	getimage_pngfile(IMG_BossRing[10],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb010.png");
	getimage_pngfile(IMG_BossRing[11],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb011.png");
	getimage_pngfile(IMG_BossRing[12],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb012.png");
	getimage_pngfile(IMG_BossRing[13],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb013.png");
	getimage_pngfile(IMG_BossRing[14],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb014.png");
	getimage_pngfile(IMG_BossRing[15],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb015.png");
	getimage_pngfile(IMG_BossRing[16],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb016.png");
	getimage_pngfile(IMG_BossRing[17],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb017.png");
	getimage_pngfile(IMG_BossRing[18],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb018.png");
	getimage_pngfile(IMG_BossRing[19],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb019.png");
	getimage_pngfile(IMG_BossRing[20],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb020.png");
	getimage_pngfile(IMG_BossRing[21],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb021.png");
	getimage_pngfile(IMG_BossRing[22],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb022.png");
	getimage_pngfile(IMG_BossRing[23],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb023.png");
	getimage_pngfile(IMG_BossRing[24],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb024.png");
	getimage_pngfile(IMG_BossRing[25],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb025.png");
	getimage_pngfile(IMG_BossRing[26],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb026.png");
	getimage_pngfile(IMG_BossRing[27],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb027.png");
	getimage_pngfile(IMG_BossRing[28],"PlayerImage\\Enemy\\Boss\\Laser\\data_character_marisa_bulletEb028.png");
	ProgressBar(500);
	getimage_pngfile(IMG_Remilia_Move_L[0],"PlayerImage\\Walk\\data_character_remilia_walkBack000.png");
	getimage_pngfile(IMG_Remilia_Move_L[1],"PlayerImage\\Walk\\data_character_remilia_walkBack001.png");
	getimage_pngfile(IMG_Remilia_Move_L[2],"PlayerImage\\Walk\\data_character_remilia_walkBack002.png");
	getimage_pngfile(IMG_Remilia_Move_L[3],"PlayerImage\\Walk\\data_character_remilia_walkBack003.png");
	getimage_pngfile(IMG_Remilia_Move_L[4],"PlayerImage\\Walk\\data_character_remilia_walkBack004.png");
	getimage_pngfile(IMG_Remilia_Move_L[5],"PlayerImage\\Walk\\data_character_remilia_walkBack005.png");
	getimage_pngfile(IMG_Remilia_Move_L[6],"PlayerImage\\Walk\\data_character_remilia_walkBack006.png");
	getimage_pngfile(IMG_Remilia_Move_L[7],"PlayerImage\\Walk\\data_character_remilia_walkBack007.png");
	getimage_pngfile(IMG_Remilia_Move_L[8],"PlayerImage\\Walk\\data_character_remilia_walkBack008.png");
	getimage_pngfile(IMG_Remilia_Move_R[0],"PlayerImage\\Walk\\data_character_remilia_walkFront000.png");
	getimage_pngfile(IMG_Remilia_Move_R[1],"PlayerImage\\Walk\\data_character_remilia_walkFront001.png");
	getimage_pngfile(IMG_Remilia_Move_R[2],"PlayerImage\\Walk\\data_character_remilia_walkFront002.png");
	getimage_pngfile(IMG_Remilia_Move_R[3],"PlayerImage\\Walk\\data_character_remilia_walkFront003.png");
	getimage_pngfile(IMG_Remilia_Move_R[4],"PlayerImage\\Walk\\data_character_remilia_walkFront004.png");
	getimage_pngfile(IMG_Remilia_Move_R[5],"PlayerImage\\Walk\\data_character_remilia_walkFront005.png");
	getimage_pngfile(IMG_Remilia_Move_R[6],"PlayerImage\\Walk\\data_character_remilia_walkFront006.png");
	getimage_pngfile(IMG_Remilia_Move_R[7],"PlayerImage\\Walk\\data_character_remilia_walkFront007.png");
	getimage_pngfile(IMG_Defense_R[0],"PlayerImage\\defenseR1.png");
	getimage_pngfile(IMG_Defense_R[1],"PlayerImage\\defenseR2.png");
	getimage_pngfile(IMG_Defense_L[0],"PlayerImage\\defenseL1.png");
	getimage_pngfile(IMG_Defense_L[1],"PlayerImage\\defenseL2.png");
	getimage_pngfile(IMG_Remilia_Stand_L[0],"PlayerImage\\Stand\\remilia_stand_L1.png");
	getimage_pngfile(IMG_Remilia_Stand_L[1],"PlayerImage\\Stand\\remilia_stand_L2.png");
	getimage_pngfile(IMG_Remilia_Stand_L[2],"PlayerImage\\Stand\\remilia_stand_L3.png");
	getimage_pngfile(IMG_Remilia_Stand_L[3],"PlayerImage\\Stand\\remilia_stand_L4.png");
	getimage_pngfile(IMG_Remilia_Stand_L[4],"PlayerImage\\Stand\\remilia_stand_L5.png");
	getimage_pngfile(IMG_Remilia_Stand_L[5],"PlayerImage\\Stand\\remilia_stand_L6.png");
	getimage_pngfile(IMG_Remilia_Stand_L[6],"PlayerImage\\Stand\\remilia_stand_L7.png");
	getimage_pngfile(IMG_Remilia_Stand_L[7],"PlayerImage\\Stand\\remilia_stand_L8.png");
	getimage_pngfile(IMG_Remilia_Stand_R[0],"PlayerImage\\Stand\\remilia_stand_R1.png");
	getimage_pngfile(IMG_Remilia_Stand_R[1],"PlayerImage\\Stand\\remilia_stand_R2.png");
	getimage_pngfile(IMG_Remilia_Stand_R[2],"PlayerImage\\Stand\\remilia_stand_R3.png");
	getimage_pngfile(IMG_Remilia_Stand_R[3],"PlayerImage\\Stand\\remilia_stand_R4.png");
	getimage_pngfile(IMG_Remilia_Stand_R[4],"PlayerImage\\Stand\\remilia_stand_R5.png");
	getimage_pngfile(IMG_Remilia_Stand_R[5],"PlayerImage\\Stand\\remilia_stand_R6.png");
	getimage_pngfile(IMG_Remilia_Stand_R[6],"PlayerImage\\Stand\\remilia_stand_R7.png");
	getimage_pngfile(IMG_Remilia_Stand_R[7],"PlayerImage\\Stand\\remilia_stand_R8.png");
	ProgressBar(560);
	getimage_pngfile(IMG_Remilia_SkillStart_BL[0],"PlayerImage\\Skill_B\\remilia_SkillB_ActionL01.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[1],"PlayerImage\\Skill_B\\remilia_SkillB_ActionL02.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[2],"PlayerImage\\Skill_B\\remilia_SkillB_ActionL03.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[3],"PlayerImage\\Skill_B\\remilia_SkillB_ActionL04.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[4],"PlayerImage\\Skill_B\\remilia_SkillB_ActionL05.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[5],"PlayerImage\\Skill_B\\remilia_SkillB_ActionL06.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[6],"PlayerImage\\Skill_B\\remilia_SkillB_ActionL07.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[7],"PlayerImage\\Skill_B\\remilia_SkillB_ActionL08.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[8],"PlayerImage\\Skill_B\\remilia_SkillB_ActionL09.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[9],"PlayerImage\\Skill_B\\remilia_SkillB_ActionL10.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[10],"PlayerImage\\Skill_B\\remilia_SkillB_ActionL11.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[11],"PlayerImage\\Skill_B\\remilia_SkillB_L01.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[12],"PlayerImage\\Skill_B\\remilia_SkillB_L02.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[13],"PlayerImage\\Skill_B\\remilia_SkillB_L03.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[14],"PlayerImage\\Skill_B\\remilia_SkillB_L04.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[15],"PlayerImage\\Skill_B\\remilia_SkillB_L05.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[16],"PlayerImage\\Skill_B\\remilia_SkillB_L06.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[17],"PlayerImage\\Skill_B\\remilia_SkillB_L07.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[18],"PlayerImage\\Skill_B\\remilia_SkillB_L08.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[19],"PlayerImage\\Skill_B\\remilia_SkillB_L09.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[20],"PlayerImage\\Skill_B\\remilia_SkillB_L10.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[21],"PlayerImage\\Skill_B\\remilia_SkillB_L11.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[22],"PlayerImage\\Skill_B\\remilia_SkillB_L12.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[23],"PlayerImage\\Skill_B\\remilia_SkillB_L13.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BL[24],"PlayerImage\\Skill_B\\remilia_SkillB_L14.png");
	ProgressBar(600);
	getimage_pngfile(IMG_Remilia_SkillStart_BR[0],"PlayerImage\\Skill_B\\remilia_SkillB_ActionR01.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[1],"PlayerImage\\Skill_B\\remilia_SkillB_ActionR02.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[2],"PlayerImage\\Skill_B\\remilia_SkillB_ActionR03.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[3],"PlayerImage\\Skill_B\\remilia_SkillB_ActionR04.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[4],"PlayerImage\\Skill_B\\remilia_SkillB_ActionR05.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[5],"PlayerImage\\Skill_B\\remilia_SkillB_ActionR06.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[6],"PlayerImage\\Skill_B\\remilia_SkillB_ActionR07.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[7],"PlayerImage\\Skill_B\\remilia_SkillB_ActionR08.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[8],"PlayerImage\\Skill_B\\remilia_SkillB_ActionR09.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[9],"PlayerImage\\Skill_B\\remilia_SkillB_ActionR10.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[10],"PlayerImage\\Skill_B\\remilia_SkillB_ActionR11.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[11],"PlayerImage\\Skill_B\\remilia_SkillB_R01.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[12],"PlayerImage\\Skill_B\\remilia_SkillB_R02.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[13],"PlayerImage\\Skill_B\\remilia_SkillB_R03.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[14],"PlayerImage\\Skill_B\\remilia_SkillB_R04.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[15],"PlayerImage\\Skill_B\\remilia_SkillB_R05.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[16],"PlayerImage\\Skill_B\\remilia_SkillB_R06.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[17],"PlayerImage\\Skill_B\\remilia_SkillB_R07.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[18],"PlayerImage\\Skill_B\\remilia_SkillB_R08.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[19],"PlayerImage\\Skill_B\\remilia_SkillB_R09.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[20],"PlayerImage\\Skill_B\\remilia_SkillB_R10.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[21],"PlayerImage\\Skill_B\\remilia_SkillB_R11.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[22],"PlayerImage\\Skill_B\\remilia_SkillB_R12.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[23],"PlayerImage\\Skill_B\\remilia_SkillB_R13.png");
	getimage_pngfile(IMG_Remilia_SkillStart_BR[24],"PlayerImage\\Skill_B\\remilia_SkillB_R14.png");
	ProgressBar(650);
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[0],"PlayerImage\\Skill_B\\remilia_SkillB_L15.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[1],"PlayerImage\\Skill_B\\remilia_SkillB_L16.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[2],"PlayerImage\\Skill_B\\remilia_SkillB_L17.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[3],"PlayerImage\\Skill_B\\remilia_SkillB_L18.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[4],"PlayerImage\\Skill_B\\remilia_SkillB_L19.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[5],"PlayerImage\\Skill_B\\remilia_SkillB_L20.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[6],"PlayerImage\\Skill_B\\remilia_SkillB_L21.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[7],"PlayerImage\\Skill_B\\remilia_SkillB_L22.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[8],"PlayerImage\\Skill_B\\remilia_SkillB_L23.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[9],"PlayerImage\\Skill_B\\remilia_SkillB_L24.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[10],"PlayerImage\\Skill_B\\remilia_SkillB_L25.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[11],"PlayerImage\\Skill_B\\remilia_SkillB_L26.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[12],"PlayerImage\\Skill_B\\remilia_SkillB_L27.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[13],"PlayerImage\\Skill_B\\remilia_SkillB_L28.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[14],"PlayerImage\\Skill_B\\remilia_SkillB_L29.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[15],"PlayerImage\\Skill_B\\remilia_SkillB_L30.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[16],"PlayerImage\\Skill_B\\remilia_SkillB_L31.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[17],"PlayerImage\\Skill_B\\remilia_SkillB_L32.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[18],"PlayerImage\\Skill_B\\remilia_SkillB_L33.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BL[19],"PlayerImage\\Skill_B\\remilia_SkillB_L34.png");
	getimage_pngfile(IMG_Remilia_Barrage[0],"PlayerImage\\barrage\\barrage1.png");
	getimage_pngfile(IMG_Remilia_Barrage[1],"PlayerImage\\barrage\\barrage2.png");
	getimage_pngfile(IMG_Remilia_Barrage[2],"PlayerImage\\barrage\\barrage3.png");
	getimage_pngfile(IMG_Remilia_Barrage[3],"PlayerImage\\barrage\\barrage4.png");
	getimage_pngfile(IMG_Remilia_Barrage[4],"PlayerImage\\barrage\\barrage5.png");
	getimage_pngfile(IMG_Remilia_Barrage[5],"PlayerImage\\barrage\\barrage6.png");
	getimage_pngfile(IMG_Remilia_Barrage[6],"PlayerImage\\barrage\\barrage7.png");
	getimage_pngfile(IMG_Remilia_BarrageAct[0],"PlayerImage\\barrage\\0.png");
	getimage_pngfile(IMG_Remilia_BarrageAct[1],"PlayerImage\\barrage\\1.png");
	getimage_pngfile(IMG_Remilia_BarrageAct[2],"PlayerImage\\barrage\\2.png");
	ProgressBar(690);
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[0],"PlayerImage\\Skill_B\\remilia_SkillB_R15.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[1],"PlayerImage\\Skill_B\\remilia_SkillB_R16.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[2],"PlayerImage\\Skill_B\\remilia_SkillB_R17.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[3],"PlayerImage\\Skill_B\\remilia_SkillB_R18.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[4],"PlayerImage\\Skill_B\\remilia_SkillB_R19.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[5],"PlayerImage\\Skill_B\\remilia_SkillB_R20.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[6],"PlayerImage\\Skill_B\\remilia_SkillB_R21.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[7],"PlayerImage\\Skill_B\\remilia_SkillB_R22.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[8],"PlayerImage\\Skill_B\\remilia_SkillB_R23.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[9],"PlayerImage\\Skill_B\\remilia_SkillB_R24.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[10],"PlayerImage\\Skill_B\\remilia_SkillB_R25.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[11],"PlayerImage\\Skill_B\\remilia_SkillB_R26.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[12],"PlayerImage\\Skill_B\\remilia_SkillB_R27.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[13],"PlayerImage\\Skill_B\\remilia_SkillB_R28.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[14],"PlayerImage\\Skill_B\\remilia_SkillB_R29.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[15],"PlayerImage\\Skill_B\\remilia_SkillB_R30.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[16],"PlayerImage\\Skill_B\\remilia_SkillB_R31.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[17],"PlayerImage\\Skill_B\\remilia_SkillB_R32.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[18],"PlayerImage\\Skill_B\\remilia_SkillB_R33.png");
	getimage_pngfile(IMG_Remilia_SkillArrow_BR[19],"PlayerImage\\Skill_B\\remilia_SkillB_R34.png");
	getimage_pngfile(IMG_RemSkillB_HitEffect,"PlayerImage\\Skill_B\\HitEffect.png");
	getimage_pngfile(IMG_Rem_NorAtkAct_R,"PlayerImage\\NormalAttack.png");
	getimage_pngfile(IMG_Rem_NorAtkAct_L,"PlayerImage\\NormalAttackL.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[0],"PlayerImage\\Enemy\\Cerulean_1.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[1],"PlayerImage\\Enemy\\Cerulean_2.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[2],"PlayerImage\\Enemy\\Cerulean_3.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[3],"PlayerImage\\Enemy\\Cerulean_4.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[4],"PlayerImage\\Enemy\\Cerulean_5.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[5],"PlayerImage\\Enemy\\Cerulean_6.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[6],"PlayerImage\\Enemy\\Cerulean_7.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[7],"PlayerImage\\Enemy\\Cerulean_8.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[8],"PlayerImage\\Enemy\\Cerulean_9.png");
	ProgressBar(750);
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[9],"PlayerImage\\Enemy\\Cerulean_10.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[10],"PlayerImage\\Enemy\\Cerulean_11.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[11],"PlayerImage\\Enemy\\Cerulean_12.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[12],"PlayerImage\\Enemy\\Cerulean_13.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_L[13],"PlayerImage\\Enemy\\Cerulean_14.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[0],"PlayerImage\\Enemy\\Cerulean_R01.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[1],"PlayerImage\\Enemy\\Cerulean_R02.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[2],"PlayerImage\\Enemy\\Cerulean_R03.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[3],"PlayerImage\\Enemy\\Cerulean_R04.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[4],"PlayerImage\\Enemy\\Cerulean_R05.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[5],"PlayerImage\\Enemy\\Cerulean_R06.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[6],"PlayerImage\\Enemy\\Cerulean_R07.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[7],"PlayerImage\\Enemy\\Cerulean_R08.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[8],"PlayerImage\\Enemy\\Cerulean_R09.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[9],"PlayerImage\\Enemy\\Cerulean_R10.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[10],"PlayerImage\\Enemy\\Cerulean_R11.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[11],"PlayerImage\\Enemy\\Cerulean_R12.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[12],"PlayerImage\\Enemy\\Cerulean_R13.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Blue_R[13],"PlayerImage\\Enemy\\Cerulean_R14.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[0],"PlayerImage\\Enemy\\Cerulean_PINK\\0.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[1],"PlayerImage\\Enemy\\Cerulean_PINK\\1.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[2],"PlayerImage\\Enemy\\Cerulean_PINK\\2.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[3],"PlayerImage\\Enemy\\Cerulean_PINK\\3.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[4],"PlayerImage\\Enemy\\Cerulean_PINK\\4.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[5],"PlayerImage\\Enemy\\Cerulean_PINK\\5.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[6],"PlayerImage\\Enemy\\Cerulean_PINK\\6.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[7],"PlayerImage\\Enemy\\Cerulean_PINK\\7.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[8],"PlayerImage\\Enemy\\Cerulean_PINK\\8.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[9],"PlayerImage\\Enemy\\Cerulean_PINK\\9.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[10],"PlayerImage\\Enemy\\Cerulean_PINK\\10.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[11],"PlayerImage\\Enemy\\Cerulean_PINK\\11.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[12],"PlayerImage\\Enemy\\Cerulean_PINK\\12.png");
	getimage_pngfile(IMG_Enemy_Cerulean_Pink[13],"PlayerImage\\Enemy\\Cerulean_PINK\\13.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_L[0],"PlayerImage\\Enemy\\AttackNormal\\L1.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_L[1],"PlayerImage\\Enemy\\AttackNormal\\L2.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_L[2],"PlayerImage\\Enemy\\AttackNormal\\L3.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_L[3],"PlayerImage\\Enemy\\AttackNormal\\L4.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_L[4],"PlayerImage\\Enemy\\AttackNormal\\L5.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_L[5],"PlayerImage\\Enemy\\AttackNormal\\L6.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_L[6],"PlayerImage\\Enemy\\AttackNormal\\L7.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_L[7],"PlayerImage\\Enemy\\AttackNormal\\L8.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_R[0],"PlayerImage\\Enemy\\AttackNormal\\R1.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_R[1],"PlayerImage\\Enemy\\AttackNormal\\R2.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_R[2],"PlayerImage\\Enemy\\AttackNormal\\R3.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_R[3],"PlayerImage\\Enemy\\AttackNormal\\R4.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_R[4],"PlayerImage\\Enemy\\AttackNormal\\R5.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_R[5],"PlayerImage\\Enemy\\AttackNormal\\R6.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_R[6],"PlayerImage\\Enemy\\AttackNormal\\R7.png");
	getimage_pngfile(IMG_Enemy_Attack_Normal_R[7],"PlayerImage\\Enemy\\AttackNormal\\R8.png");
	ProgressBar(820);
	getimage_pngfile(IMG_Enemy_CerBlue_Death[0],"PlayerImage\\Enemy\\BlueDeath\\1.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[1],"PlayerImage\\Enemy\\BlueDeath\\2.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[2],"PlayerImage\\Enemy\\BlueDeath\\3.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[3],"PlayerImage\\Enemy\\BlueDeath\\4.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[4],"PlayerImage\\Enemy\\BlueDeath\\5.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[5],"PlayerImage\\Enemy\\BlueDeath\\6.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[6],"PlayerImage\\Enemy\\BlueDeath\\7.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[7],"PlayerImage\\Enemy\\BlueDeath\\8.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[8],"PlayerImage\\Enemy\\BlueDeath\\9.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[9],"PlayerImage\\Enemy\\BlueDeath\\10.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[10],"PlayerImage\\Enemy\\BlueDeath\\11.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[11],"PlayerImage\\Enemy\\BlueDeath\\12.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[12],"PlayerImage\\Enemy\\BlueDeath\\13.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[13],"PlayerImage\\Enemy\\BlueDeath\\14.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[14],"PlayerImage\\Enemy\\BlueDeath\\15.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[15],"PlayerImage\\Enemy\\BlueDeath\\16.png");
	getimage_pngfile(IMG_Enemy_CerBlue_Death[16],"PlayerImage\\Enemy\\BlueDeath\\17.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[0],"PlayerImage\\Enemy\\PinkDeath\\1.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[1],"PlayerImage\\Enemy\\PinkDeath\\2.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[2],"PlayerImage\\Enemy\\PinkDeath\\3.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[3],"PlayerImage\\Enemy\\PinkDeath\\4.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[4],"PlayerImage\\Enemy\\PinkDeath\\5.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[5],"PlayerImage\\Enemy\\PinkDeath\\6.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[6],"PlayerImage\\Enemy\\PinkDeath\\7.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[7],"PlayerImage\\Enemy\\PinkDeath\\8.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[8],"PlayerImage\\Enemy\\PinkDeath\\9.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[9],"PlayerImage\\Enemy\\PinkDeath\\10.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[10],"PlayerImage\\Enemy\\PinkDeath\\11.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[11],"PlayerImage\\Enemy\\PinkDeath\\12.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[12],"PlayerImage\\Enemy\\PinkDeath\\13.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[13],"PlayerImage\\Enemy\\PinkDeath\\14.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[14],"PlayerImage\\Enemy\\PinkDeath\\15.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[15],"PlayerImage\\Enemy\\PinkDeath\\16.png");
	getimage_pngfile(IMG_Enemy_CerPink_Death[16],"PlayerImage\\Enemy\\PinkDeath\\17.png");
	ProgressBar(870);
	getimage_pngfile(IMG_Boss[0],"PlayerImage\\Enemy\\Boss\\0.png");
	getimage_pngfile(IMG_Boss[1],"PlayerImage\\Enemy\\Boss\\1.png");
	getimage_pngfile(IMG_Boss[2],"PlayerImage\\Enemy\\Boss\\2.png");
	getimage_pngfile(IMG_Boss[3],"PlayerImage\\Enemy\\Boss\\3.png");
	getimage_pngfile(IMG_Boss[4],"PlayerImage\\Enemy\\Boss\\4.png");
	getimage_pngfile(IMG_Boss[5],"PlayerImage\\Enemy\\Boss\\5.png");
	getimage_pngfile(IMG_Boss[6],"PlayerImage\\Enemy\\Boss\\6.png");
	getimage_pngfile(IMG_Boss[7],"PlayerImage\\Enemy\\Boss\\7.png");
	getimage_pngfile(IMG_Boss[8],"PlayerImage\\Enemy\\Boss\\8.png");
	getimage_pngfile(IMG_Boss[9],"PlayerImage\\Enemy\\Boss\\9.png");
	getimage_pngfile(IMG_Boss[10],"PlayerImage\\Enemy\\Boss\\10.png");
	getimage_pngfile(IMG_Boss[11],"PlayerImage\\Enemy\\Boss\\11.png");
	getimage_pngfile(IMG_Boss[12],"PlayerImage\\Enemy\\Boss\\12.png");
	getimage_pngfile(IMG_Boss[13],"PlayerImage\\Enemy\\Boss\\13.png");
	getimage_pngfile(IMG_Boss[14],"PlayerImage\\Enemy\\Boss\\14.png");
	getimage_pngfile(IMG_Boss[15],"PlayerImage\\Enemy\\Boss\\15.png");
	getimage_pngfile(IMG_Boss[16],"PlayerImage\\Enemy\\Boss\\16.png");
	getimage_pngfile(IMG_Boss[17],"PlayerImage\\Enemy\\Boss\\17.png");
	getimage_pngfile(IMG_Boss[18],"PlayerImage\\Enemy\\Boss\\18.png");
	getimage_pngfile(IMG_Boss[19],"PlayerImage\\Enemy\\Boss\\19.png");
	getimage_pngfile(IMG_Remilia_Start[0],"PlayerImage\\Start\\Start01.png");
	getimage_pngfile(IMG_Remilia_Start[1],"PlayerImage\\Start\\Start02.png");
	getimage_pngfile(IMG_Remilia_Start[2],"PlayerImage\\Start\\Start03.png");
	getimage_pngfile(IMG_Remilia_Start[3],"PlayerImage\\Start\\Start04.png");
	getimage_pngfile(IMG_Remilia_Start[4],"PlayerImage\\Start\\Start05.png");
	getimage_pngfile(IMG_Remilia_Start[5],"PlayerImage\\Start\\Start06.png");
	getimage_pngfile(IMG_Remilia_Start[6],"PlayerImage\\Start\\Start07.png");
	getimage_pngfile(IMG_Remilia_Start[7],"PlayerImage\\Start\\Start08.png");
	getimage_pngfile(IMG_Remilia_Start[8],"PlayerImage\\Start\\Start09.png");
	getimage_pngfile(IMG_Remilia_Start[9],"PlayerImage\\Start\\Start10.png");
	ProgressBar(900);
	getimage_pngfile(IMG_Remilia_Start[10],"PlayerImage\\Start\\data_character_remilia_spellFa000.png");
	getimage_pngfile(IMG_Remilia_Start[11],"PlayerImage\\Start\\data_character_remilia_spellFa001.png");
	getimage_pngfile(IMG_Remilia_Start[12],"PlayerImage\\Start\\data_character_remilia_spellFa002.png");
	getimage_pngfile(IMG_Remilia_Start[13],"PlayerImage\\Start\\data_character_remilia_spellFa003.png");
	getimage_pngfile(IMG_Remilia_Start[14],"PlayerImage\\Start\\data_character_remilia_spellFa004.png");
	getimage_pngfile(IMG_Remilia_Start[15],"PlayerImage\\Start\\data_character_remilia_spellFa005.png");
	getimage_pngfile(IMG_Remilia_Start[16],"PlayerImage\\Start\\data_character_remilia_spellFa006.png");
	getimage_pngfile(IMG_Remilia_Start[17],"PlayerImage\\Start\\data_character_remilia_spellFa007.png");
	getimage_pngfile(IMG_Remilia_Start[18],"PlayerImage\\Start\\data_character_remilia_spellFa008.png");
	getimage_pngfile(IMG_Remilia_Start[19],"PlayerImage\\Start\\data_character_remilia_spellFa009.png");
	getimage_pngfile(IMG_Remilia_Skill_AL,"PlayerImage\\Skill_A_L.png");
	getimage_pngfile(IMG_Remilia_Skill_AR,"PlayerImage\\Skill_A_R.png");
	getimage_pngfile(IMG_Remilia_Death_L,"PlayerImage\\Death_L.png");
	getimage_pngfile(IMG_Remilia_Death_R,"PlayerImage\\Death_R.png");
	getimage_pngfile(IMG_Remilia_Beaten_L,"PlayerImage\\Beaten_L.png");
	getimage_pngfile(IMG_Remilia_Beaten_R,"PlayerImage\\Beaten_R.png");
	getimage_pngfile(IMG_Gameover,"ScenesImage\\Menu\\gameover.png");
	getimage_pngfile(IMG_HPMPBar,"ScenesImage\\Menu\\HPMPbar\\boder.GUI");
	getimage_pngfile(IMG_BossHPMPBar_1,"ScenesImage\\Menu\\HPMPbar\\bossboder1.GUI");
	getimage_pngfile(IMG_BossHPMPBar_2,"ScenesImage\\Menu\\HPMPbar\\bossboder2.GUI");
	getimage_pngfile(IMG_Reply_Props[0],"ScenesImage\\reply_hpprops\\1.png");
	getimage_pngfile(IMG_Reply_Props[1],"ScenesImage\\reply_hpprops\\2.png");
	getimage_pngfile(IMG_Reply_Props[2],"ScenesImage\\reply_hpprops\\3.png");
	getimage_pngfile(IMG_Reply_Props[3],"ScenesImage\\reply_hpprops\\4.png");
	getimage_pngfile(IMG_Reply_Props[4],"ScenesImage\\reply_hpprops\\5.png");
	getimage_pngfile(IMG_Reply_Props[5],"ScenesImage\\reply_hpprops\\6.png");
	getimage_pngfile(IMG_Reply_Props[6],"ScenesImage\\reply_hpprops\\7.png");
	getimage_pngfile(IMG_Reply_Props[7],"ScenesImage\\reply_hpprops\\8.png");
	getimage_pngfile(IMG_Reply_Props[8],"ScenesImage\\reply_hpprops\\9.png");
	getimage_pngfile(IMG_Reply_Props[9],"ScenesImage\\reply_hpprops\\10.png");
	getimage_pngfile(IMG_Reply_Props[10],"ScenesImage\\reply_hpprops\\11.png");
	getimage_pngfile(IMG_Reply_Props[11],"ScenesImage\\reply_hpprops\\12.png");
	getimage_pngfile(IMG_Reply_Eft[0],"ScenesImage\\reply_hpprops\\eft\\1.png");
	getimage_pngfile(IMG_Reply_Eft[1],"ScenesImage\\reply_hpprops\\eft\\2.png");
	getimage_pngfile(IMG_Reply_Eft[2],"ScenesImage\\reply_hpprops\\eft\\3.png");
	getimage_pngfile(IMG_Reply_Eft[3],"ScenesImage\\reply_hpprops\\eft\\4.png");
	getimage_pngfile(IMG_Reply_Eft[4],"ScenesImage\\reply_hpprops\\eft\\5.png");
	getimage_pngfile(IMG_Reply_Eft[5],"ScenesImage\\reply_hpprops\\eft\\6.png");
	getimage_pngfile(IMG_Reply_Eft[6],"ScenesImage\\reply_hpprops\\eft\\7.png");
	getimage_pngfile(IMG_Reply_Eft[7],"ScenesImage\\reply_hpprops\\eft\\8.png");
	getimage_pngfile(IMG_Reply_Eft[8],"ScenesImage\\reply_hpprops\\eft\\9.png");
	getimage(IMG_Background_A,"ScenesImage\\BackGround.jpg");
	getimage(IMG_Background_B,"ScenesImage\\BackGroundReverse.jpg");
	ProgressBar(930);
}

/************************************/
/*函数名：Graphics_R_Shift	 		*/
/*功  能：右移屏			 		*/
/*参  数：			 		 		*/
/*返回值： 		 					*/
/************************************/
void Graphics_R_Shift(void)
{	
	//换页处理 
	if(Remilia.x == Page_BorderLine[Current_Page] && Remilia.Flag_Direction)
		Current_Page++;
	if(Current_Page!=0)
		if(Remilia.x == Page_BorderLine[Current_Page-1] && !Remilia.Flag_Direction)
			Current_Page--;

	if(Remilia.x == ShiftScreen_R_Xlocation)
	{
		int i=0,j=0;
		
		Remilia.x = ShiftScreen_R_Xlocation-1;
		
		for(i=0;i<Page_Amount;i++)
		{
			for(j=0;j<Page_BlockAmount[i];j++)
			{
				MapData_Block[i][j].x--;
			}
			for(j=0;j<Page_EnemyTypeAmount[i][0];j++)
			{
				MapData_Enemy[i][j].x--;
			}
			Page_BorderLine[i]--;
		}
		
		ScreenShiftDirection = 1;
		CurrentScreen_Xaxis++;
		Anime_PlayerMoveR();
	}
}

/************************************/
/*函数名：Graphics_L_Shift	 		*/
/*功  能：左移屏			 		*/
/*参  数：			 		 		*/
/*返回值： 		 					*/
/************************************/
void Graphics_L_Shift(void)
{	
	//换页处理 
	if(Remilia.x == Page_BorderLine[Current_Page-1] && !Remilia.Flag_Direction)
		if(Current_Page!=0)
			Current_Page--;
	if(Remilia.x == Page_BorderLine[Current_Page] && Remilia.Flag_Direction)
		Current_Page++;
			
	if(Remilia.x == ShiftScreen_L_Xlocation)
	{
		int i=0,j=0;
		
		Remilia.x = ShiftScreen_L_Xlocation+1;
		
		for(i=0;i<Page_Amount;i++)
		{
			for(j=0;j<Page_BlockAmount[i];j++)
			{
				MapData_Block[i][j].x++;
			}
			for(j=0;j<Page_EnemyTypeAmount[i][0];j++)
			{
				MapData_Enemy[i][j].x++;
			}
			Page_BorderLine[i]++;
		}
			
		ScreenShiftDirection = 0;
		CurrentScreen_Xaxis--;
		Anime_PlayerMoveL();
	}
	
}

/************************************/
/*函数名：Graphics_AuxiliaryGrid	*/
/*功  能：绘制辅助网格			 	*/
/*参  数：网格间距					*/
/*返回值： 		 					*/
/************************************/
void Graphics_AuxiliaryGrid(int Spacing)
{
	int Grid;
	setcolor(EGERGB(255,255,254));
	for(Grid=0;Grid<WindowSize_L;Grid+=Spacing){
		line(Grid,0,Grid,WindowSize_H);
	}
	for(Grid=0;Grid<WindowSize_H;Grid+=Spacing){
		line(0,Grid,WindowSize_L,Grid);
	}
}

/************************************/
/*函数名： SYS_Block_Set			*/
/*功  能： Block对象参数设定		*/
/*参  数： 对象结构体指针 			*/
/*		   对象左上坐标				*/
/*		   对象右下坐标				*/
/*		   对象状态 				*/
/*返回值： 		 					*/
/************************************/
void SYS_Block_Set(Object_Parameter *Block,int x1,int y1,int x2,int y2,int Type)
{
	Block->x=x1;
	Block->y=y1;
	#ifdef ENABLE_LWSetMode
	Block->Length=x2;
	Block->Width=y2;
	#else
	Block->Length=(x2-x1);
	Block->Width=(y2-y1);
	#endif
	Block->type=Type;
}

/************************************/
/*函数名： SYS_Player_Init			*/
/*功  能： 初始化Remilia		 	*/
/*参  数： 		 					*/
/*返回值： 		 					*/
/************************************/
void SYS_Player_Init(void)
{
	
	//基础属性设定 
	Remilia.x = Remilia_initX;
	Remilia.y = Remilia_initY;
	Remilia.Length = Remilia_Length;
	Remilia.Width = Remilia_Width;
	Remilia.HP = Remilia_HP;
	Remilia.MP = Remilia_MP;
	Remilia.BeatenBossBarrage_Ctr = 0;
	Remilia.BeatenBossLaser_Ctr = 0;
	Remilia.BeatenBoss_Spd = 0;
	Remilia.Flag_Beaten = 0;
	Remilia.Flag_Direction = 1;
	Remilia.Flag_Death = 0;
	Remilia.Flag_Jump = 0;
	Remilia.Defense = 0;
	Remilia.Flag_Barrage = 0;
	
	//普通攻击属性设定
	Remilia_NorAtk_A.Flag_Direction = 1;
	Remilia_NorAtk_A.Damage = NorAtk_Damage_A;
	Remilia_NorAtk_A.Length = 105;
	Remilia_NorAtk_A.Width = 64;
	Remilia_NorAtk_A.type = 31;
	Remilia_NorAtk_A.x = -100;
	Remilia_NorAtk_A.y = -100;
	
	Remilia_NorAtk_B.Flag_Direction = 1;
	Remilia_NorAtk_B.Damage = NorAtk_Damage_B;
	Remilia_NorAtk_B.Length = 105;
	Remilia_NorAtk_B.Width = 64;
	Remilia_NorAtk_B.type = 32;
	Remilia_NorAtk_B.x = -100;
	Remilia_NorAtk_B.y = -100;
	
	Remilia_NorAtk_C.Flag_Direction = 1;
	Remilia_NorAtk_C.Damage = NorAtk_Damage_C;
	Remilia_NorAtk_C.Length = 105;
	Remilia_NorAtk_C.Width = 128;
	Remilia_NorAtk_C.type = 33;
	Remilia_NorAtk_C.x = -100;
	Remilia_NorAtk_C.y = -100;
	
	//技能A属性设定 
	Remilia_Skill_A.Flag_Direction = 1;
	Remilia_Skill_A.Damage = SkillA_Damage;		//伤害值 
	Remilia_Skill_A.Length = 128;		//攻击范围 
	Remilia_Skill_A.Width = 128;		
	Remilia_Skill_A.type = 1;
	Remilia_Skill_A.x = -100;
	Remilia_Skill_A.y = -100;
	
	//技能B属性设定
	Remilia_Skill_B.Flag_Direction = 1;
    Remilia_Skill_B.Damage = SkillB_Damage;
    Remilia_Skill_B.Length = 160;
    Remilia_Skill_B.Width = 64;
    Remilia_Skill_B.type = 2;
    Remilia_Skill_B.x = -100;
	Remilia_Skill_B.y = -100;
	
}

/************************************/
/*函数名： SYS_Music_Init			*/
/*功  能： 音乐初始化			 	*/
/*参  数： 		 					*/
/*返回值： 		 					*/
/************************************/
void SYS_Music_Init(void)
{
	#ifdef ENABLE_Music
	Music_RemSkill_A.OpenFile("Music\\RemiliaSkill_A.mp3"); 
	Music_RemSkill_A.SetVolume(0.6f);
	
	Music_RemSkill_B_Start.OpenFile("Music\\RemiliaSkill_B_Start.mp3"); 
	Music_RemSkill_B_Start.SetVolume(0.6f);
	
	Music_RemSkill_B_Flying.OpenFile("Music\\RemiliaSkill_B_Flying.mp3");
	Music_RemSkill_B_Flying.SetVolume(0.6f);
	
	Music_RemiliaDeath.OpenFile("Music\\RemiliaDeath.mp3"); 
	Music_RemiliaDeath.SetVolume(0.7f);
	
	Music_CerBlueAttN.OpenFile("Music\\CerBlueNormalAttack.mp3");
	Music_CerBlueAttN.SetVolume(0.4f);
	
	Music_GameOver.OpenFile("Music\\GameOver.mp3");
	Music_GameOver.SetVolume(0.6f);
	
	Music_GameVictory.OpenFile("Music\\gamevictory.mp3");
	Music_GameVictory.SetVolume(0.6f);
	
	Music_GUISelected_1.OpenFile("Music\\Music_GUISelected_1.mp3");
	Music_GUISelected_1.SetVolume(0.7f);
	
	Music_GUIConfirm_1.OpenFile("Music\\Music_GUIConfirm_1.mp3");
	Music_GUIConfirm_1.SetVolume(0.6f);
	
	Music_StartBGM.OpenFile("Music\\StartBGM_C160kbps.mp3"); 
	Music_StartBGM.SetVolume(0.5f);
	
	Music_BattleBGM.OpenFile("Music\\Necrofantasia_C128kbps.mp3"); 
	Music_BattleBGM.SetVolume(0.2f);
	
	Music_BossBGM.OpenFile("Music\\BossBGM_C160kbps.mp3"); 
	Music_BossBGM.SetVolume(0.2f);
	
	Music_Beaten[0].OpenFile("Music\\beaten1.mp3"); 
	Music_Beaten[0].SetVolume(0.4f);
	
	Music_Beaten[1].OpenFile("Music\\beaten2.mp3"); 
	Music_Beaten[1].SetVolume(0.4f);
	
	Music_Beaten[2].OpenFile("Music\\beaten3.mp3"); 
	Music_Beaten[2].SetVolume(0.4f);
	
	Music_NorAtk[0].OpenFile("Music\\NorAtk_A.mp3"); 
	Music_NorAtk[0].SetVolume(0.4f);
	
	Music_NorAtk[1].OpenFile("Music\\NorAtk_B.mp3");
	Music_NorAtk[1].SetVolume(0.4f);
	
	Music_NorAtk[2].OpenFile("Music\\NorAtk_C.mp3"); 
	Music_NorAtk[2].SetVolume(0.4f);
	
	Music_PinkJump.OpenFile("Music\\PinkJump.mp3");
	Music_PinkJump.SetVolume(0.3f);
	
	Music_BossBarrageFire.OpenFile("Music\\BoosBarrageFire.mp3");
	Music_BossBarrageFire.SetVolume(0.2f);
	
	Music_BossBarrageHit.OpenFile("Music\\BoosBarrageHit.mp3");
	Music_BossBarrageHit.SetVolume(0.5f);
	
	Music_BossLaser.OpenFile("Music\\bossLaserAtk.mp3");
	Music_BossLaser.SetVolume(0.3f);
	
	Music_HPreply.OpenFile(("Music\\HPreply.mp3"));
	Music_HPreply.SetVolume(0.6f);
	
	Music_Tentacle.OpenFile(("Music\\windeft.mp3"));
	Music_Tentacle.SetVolume(0.5f);
	
	Music_Blood.OpenFile(("Music\\blood.mp3"));
	Music_Blood.SetVolume(0.5f);
	
	Music_RemBarrage.OpenFile(("Music\\rembarrage.mp3"));
	Music_RemBarrage.SetVolume(1.0f);
	#endif
}

/************************************/
/*函数名： SYS_Parameter_Init		*/
/*功  能： 参数初始化			 	*/
/*参  数： 		 					*/
/*返回值： 		 					*/
/************************************/
void SYS_Parameter_Init(void)
{
	SYS_Player_Init();
	SYS_MapFile_Read(1);
	
	BossStage_Xlocation = Window_TotalLength - WindowSize_L;
	Current_Page = 0;
	CurrentScreen_Xaxis = 0;
	BeatMusRand = 0;
	MPRestore_Ctr = 0;
	Background_ReverseFlag = 1;
	ScreenShiftDirection = 1;
	Move_Jumped_Height = 0;
	Move_Jump_StartHeight = 0;
	JumpDelay = 0;
	Flag_isMoving = 0;
	DefenseFlag = 0;
	DefenseCtr = 0;
	Anime_Offset_x=Remilia_initX;
	Anime_Offset_y=Remilia_initY;
	Anime_MoveStand_FlagA = 1;
	Anime_MoveStand_FlagB = 0;
	Anime_BeatenCtrA = 1;
	Anime_BeatenCtrB = 0;
	NorAtk_CDcounter = 0; 
	NorAtk_CtrA = 1;
	NorAtk_CtrB = 0;
	NorAtkEft_CtrA = 1;
	NorAtkEft_CtrB = 0;
	NorAtk_TypeCtr = 0;
	NorAtk_Type = 1;
	NorAtk_EftStart = 0;
	SkillA_CDcounter = 0;
	Flag_isSkilling = 0;
	Anime_SkillA_FlagA = 1;
	Anime_SkillA_FlagB = 0;
	SkillB_CDcounter = 0;
	Barrage_CDcounter = 0;
	Anime_SkillB_FlagA = 0;
	Anime_SkillB_FlagB = 0;
	Anime_SkillBArrow_FlagA = 0;
	Anime_SkillBArrow_FlagB = 0;
	Anime_SkillBHitEffect_Flag = 0;
	Flag_SkillB_CD = 0;
	Flag_SkillArrow_B = 0;
	Anime_CeruBlue_CtrA = 0;
	Anime_CeruBlue_CtrB = 0;
	Anime_CeruPink_CtrA = 0;
	Anime_CeruPink_CtrB = 0;
	Anime_CerBlue_DeathFlag = 0;
	Enemy_CeruleanBlue_Flag = 0;
	Enemy_CerBlue_AttCtr = 0;
	AnimeAcitve_SPCtr = 0;
	isBossStage = 0;
	BossAtk_Barrage_Flag = -1;
	BossAtk_Ctr_A = 0;
	BossAtk_Ctr_B = 0;
	BossAtk_SpeedCtr = 0;
	Check_EnemyDamageNormal = 0;
	Flag_GUIMusStu = 0;
	Flag_GUIPicStu = 0;
	Props_ReplyHP_Ctr = 0; 
	Props_ReplyDeath_Ctr = 0;
	Barrage_Height = SkillBarrage_Height;
	Barrage_CDcounter = 0; 
	Barrage_Speed_Ctr = 0;
	Barrage_ActCtr = 0;
	Barrage_Ctr_A = 0;
	Barrage_Ctr_B = 0;
	Barrage_Flag = -1;
}

/************************************/
/*函数名： SYS_Game_Over			*/
/*功  能： 游戏结束				 	*/
/*参  数： 1游戏结束		 		*/
/*返回值： 		 					*/
/************************************/
bool SYS_Game_Over(void)
{
	
	Music_BossBGM.Stop();
	Music_BattleBGM.Stop();
	Music_RemiliaDeath.Play(0);	
	Anime_PlayerDeath();
	Music_GameOver.Play(0);
	Sleep(500);	
		
	GUI_GameOver();

	Sleep(500);
	return(1);
}

/************************************/
/*函数名： Check_Collision			*/
/*功  能： 碰撞检测		 			*/
/*参  数： 检测方向				   	*/
/*			1 X正半轴	-1 X负半轴	*/
/*			2 Y正半轴	-2 Y负半轴	*/
/*返回值：bit0:31  	1 碰撞  0 不碰撞*/
/************************************/
long long Check_Collision(int Direction)
{	
	long long Flag=0;
	int i;
	if(Direction==1)
	{
		for(i=0;i<Page_BlockAmount[Current_Page];i++)
		{
			if(Remilia.x+Remilia.Length==MapData_Block[Current_Page][i].x)//检测X正半轴碰撞 
				Flag|=1;
			Flag<<=1;
		}
		return(Flag>>1);
	}
		
	if(Direction==-1)
	{
		for(i=0;i<Page_BlockAmount[Current_Page];i++)
		{
			if(Remilia.x-MapData_Block[Current_Page][i].Length==MapData_Block[Current_Page][i].x)//检测X负半轴碰撞 
				Flag|=1;
			Flag<<=1;
		}
		return(Flag>>1);
	}
		
	if(Direction==2)
	{
		for(i=0;i<Page_BlockAmount[Current_Page];i++)
		{
			if(Remilia.y+Remilia.Width==MapData_Block[Current_Page][i].y)//检测Y正半轴碰撞
				Flag|=1;
			Flag<<=1;
		}
		return(Flag>>1);
	}
		
	if(Direction==-2)
	{
		for(i=0;i<Page_BlockAmount[Current_Page];i++)
		{
			if(Remilia.y-MapData_Block[Current_Page][i].Width==MapData_Block[Current_Page][i].y)//检测Y负半轴碰撞
				Flag|=1;
			Flag<<=1;
		}
		return(Flag>>1);
	}
}
/************************************/
/*函数名： Check_Accessible			*/
/*功  能： 通过性检测		 		*/
/*参  数： 检测方向				   	*/
/*			1 X正半轴	-1 X负半轴	*/
/*			2 Y正半轴	-2 Y负半轴	*/
/*返回值：bit0:31 1可通过  0不可通过*/
/************************************/
long long Check_Accessible(int Direction)
{
	long long Flag=0;
	int i;
	if(Direction==1)
	{
		for(i=0;i<Page_BlockAmount[Current_Page];i++)
		{
			if(Remilia.x>=MapData_Block[Current_Page][i].x+MapData_Block[Current_Page][i].Length)//X正半轴通过性检测 
				Flag|=1;
			Flag<<=1;
		}
		return(Flag>>1);
	} 	
	if(Direction==-1)
	{
		for(i=0;i<Page_BlockAmount[Current_Page];i++)
		{
			if(Remilia.x<=MapData_Block[Current_Page][i].x-Remilia.Length)//X负半轴通过性检测 
				Flag|=1;	
			Flag<<=1;
		}
		return(Flag>>1);
	} 
	if(Direction==2)
	{
		for(i=0;i<Page_BlockAmount[Current_Page];i++)
		{
			if(Remilia.y>=MapData_Block[Current_Page][i].y+MapData_Block[Current_Page][i].Width)//Y正半轴通过性检测 
				Flag|=1;
				
			Flag<<=1;
		}
		return(Flag>>1);
	} 		
	if(Direction==-2)
	{
		for(i=0;i<Page_BlockAmount[Current_Page];i++)
		{
			if(Remilia.y<=MapData_Block[Current_Page][i].y-Remilia.Width)//Y负半轴通过性检测 
				Flag|=1;
				
			Flag<<=1;
		}
		return(Flag>>1);
	} 
}

/************************************/
/*函数名： EnemyCheck_Collision		*/
/*功  能： 碰撞检测		 			*/
/*参  数： 检测方向	,敌人编号	  	*/
/*			1 X正半轴	-1 X负半轴	*/
/*			2 Y正半轴	-2 Y负半轴	*/
/*返回值：bit0:31  	1 碰撞  0 不碰撞*/
/************************************/
long long EnemyCheck_Collision(int Direction,int number,int page)
{	
	long long Flag=0;
	int i;
	
	if(Direction==1)
	{
		for(i=0;i<Page_BlockAmount[page];i++)
		{
			if(MapData_Enemy[page][number].x+MapData_Enemy[page][number].Length==MapData_Block[page][i].x)//检测X正半轴碰撞 
				Flag|=1;
			Flag<<=1;
		}
		return(Flag>>1);
	}
		
	if(Direction==-1)
	{
		for(i=0;i<Page_BlockAmount[page];i++)
		{
			if(MapData_Enemy[page][number].x-MapData_Block[page][i].Length==MapData_Block[page][i].x)//检测X负半轴碰撞 
				Flag|=1;
			Flag<<=1;
		}
		return(Flag>>1);
	}
		
	if(Direction==2)
	{
		for(i=0;i<Page_BlockAmount[page];i++)
		{
			if(MapData_Enemy[page][number].y+MapData_Enemy[page][number].Width==MapData_Block[page][i].y)//检测Y正半轴碰撞
				Flag|=1;
			Flag<<=1;
		}
		return(Flag>>1);
	}
		
	if(Direction==-2)
	{
		for(i=0;i<Page_BlockAmount[page];i++)
		{
			if(MapData_Enemy[page][number].y-MapData_Block[page][i].Width==MapData_Block[page][i].y)//检测Y负半轴碰撞
				Flag|=1;
			Flag<<=1;
		}
		return(Flag>>1);
	}	
}

/************************************/
/*函数名： EnemyCheck_Accessible	*/
/*功  能： 通过性检测		 		*/
/*参  数： 检测方向	,敌人编号	  	*/
/*			1 X正半轴	-1 X负半轴	*/
/*			2 Y正半轴	-2 Y负半轴	*/
/*返回值：bit0:31 1可通过  0不可通过*/
/************************************/
long long EnemyCheck_Accessible(int Direction,int number,int page)
{
	long long Flag=0;
	int i;
	
	if(Direction==1)
	{
		for(i=0;i<Page_BlockAmount[page];i++)
		{
			if(MapData_Enemy[page][number].x>=MapData_Block[page][i].x+MapData_Block[page][i].Length)//X正半轴通过性检测 
				Flag|=1;
			Flag<<=1;
		}
		return(Flag>>1);
	} 	
	if(Direction==-1)
	{
		for(i=0;i<Page_BlockAmount[page];i++)
		{
			if(MapData_Enemy[page][number].x<=MapData_Block[page][i].x-MapData_Enemy[page][number].Length)//X负半轴通过性检测 
				Flag|=1;	
			Flag<<=1;
		}
		return(Flag>>1);
	} 
	if(Direction==2)
	{
		for(i=0;i<Page_BlockAmount[page];i++)
		{
			if(MapData_Enemy[page][number].y>=MapData_Block[page][i].y+MapData_Block[page][i].Width)//Y正半轴通过性检测 
				Flag|=1;
				
			Flag<<=1;
		}
		return(Flag>>1);
	} 		
	if(Direction==-2)
	{
		for(i=0;i<Page_BlockAmount[page];i++)
		{
			if(MapData_Enemy[page][number].y<=MapData_Block[page][i].y-MapData_Enemy[page][number].Width)//Y负半轴通过性检测 
				Flag|=1;
				
			Flag<<=1;
		}
		return(Flag>>1);
	} 
}

/************************************/
/*函数名： Check_BelowBlock			*/
/*功  能： 下方障碍物检测		 	*/
/*参  数:-1检测玩家 else检测敌人编号*/
/*返回值：1~Block_Amount+1 			*/
/*						障碍物编号+1*/
/*		  0 						*/
/*						无障碍		*/
/************************************/
int Check_BelowBlock(int number,int page)
{
	long long collision,accessible_1,accessible_2;
	int i;
	
	if(number==-1)
	{
		collision = Check_Collision(Y_Positive);
		accessible_1 = Check_Accessible(X_Negative);
		accessible_2 = Check_Accessible(X_Positive);
	}
	else
	{
		collision = EnemyCheck_Collision(Y_Positive,number,page);
		accessible_1 = EnemyCheck_Accessible(X_Negative,number,page);
		accessible_2 = EnemyCheck_Accessible(X_Positive,number,page);
	}

	for(i=0;i<Page_BlockAmount[page];i++)
	{
		if(collision>>i&1)		//1
			if(!(accessible_1>>i&1))//0
				if(!(accessible_2>>i&1))//0
					return(i+1);
	}
	return(0);
}
/************************************/
/*函数名： Check_TopBlock			*/
/*功  能： 上方障碍物检测		 	*/
/*参  数:-1检测玩家 else检测敌人编号*/
/*返回值：1~Block_Amount+1 			*/
/*						障碍物编号+1*/
/*		  0 						*/
/*						无障碍		*/
/************************************/
int Check_TopBlock(int number,int page)
{
	long long collision,accessible_1,accessible_2;
	int i;
	
	if(number==-1)
	{
		collision = Check_Collision(Y_Negative);
		accessible_1 = Check_Accessible(X_Negative);
		accessible_2 = Check_Accessible(X_Positive);
	}
	else
	{
		collision = EnemyCheck_Collision(Y_Negative,number,page);
		accessible_1 = EnemyCheck_Accessible(X_Negative,number,page);
		accessible_2 = EnemyCheck_Accessible(X_Positive,number,page);
	}
	
	
	for(i=0;i<Page_BlockAmount[page];i++)
	{
		if(collision>>i&1)		//1
			if(!(accessible_1>>i&1))//0
				if(!(accessible_2>>i&1))//0
					return(i+1);
	}
	return(0);
}

/************************************/
/*函数名： Check_LeftBlock			*/
/*功  能： 左侧障碍物检测		 	*/
/*参  数:-1检测玩家 else检测敌人编号*/
/*返回值：1~Block_Amount+1 			*/
/*						障碍物编号+1*/
/*		  0 						*/
/*						无障碍		*/
/************************************/
int Check_LeftBlock(int number,int page)
{
	long long collision,accessible_1,accessible_2;
	int i;
	
	if(number==-1)
	{
		collision = Check_Collision(X_Negative);
		accessible_1 = Check_Accessible(Y_Negative);
		accessible_2 = Check_Accessible(Y_Positive);
	}
	else
	{
		collision = EnemyCheck_Collision(X_Negative,number,page);
		accessible_1 = EnemyCheck_Accessible(Y_Negative,number,page);
		accessible_2 = EnemyCheck_Accessible(Y_Positive,number,page);
	}
	
	for(i=0;i<Page_BlockAmount[page];i++)
	{
		if(collision>>i&1)		//1
			if(!(accessible_1>>i&1))//0
				if(!(accessible_2>>i&1))//0
					return(i+1);
	}
	return(0);
}
/************************************/
/*函数名： Check_RightBlock			*/
/*功  能： 右侧障碍物检测		 	*/
/*参  数:-1检测玩家 else检测敌人编号*/
/*返回值：1~Block_Amount+1 			*/
/*						障碍物编号+1*/
/*		  0 						*/
/*						无障碍		*/
/************************************/
int Check_RightBlock(int number,int page)
{
	long long collision,accessible_1,accessible_2;
	int i;
	
	if(number==-1)
	{
		collision = Check_Collision(X_Positive);
		accessible_1 = Check_Accessible(Y_Negative);
		accessible_2 = Check_Accessible(Y_Positive);
	}
	else
	{
		collision = EnemyCheck_Collision(X_Positive,number,page);
		accessible_1 = EnemyCheck_Accessible(Y_Negative,number,page);
		accessible_2 = EnemyCheck_Accessible(Y_Positive,number,page);
	}
	
	for(i=0;i<Page_BlockAmount[page];i++)
	{
		if(collision>>i&1)		//1
			if(!(accessible_1>>i&1))//0
				if(!(accessible_2>>i&1))//0
					return(i+1);
	}
	return(0);
}

/************************************/
/*函数名：Anime_PlayerDeath			*/
/*功  能：玩家死亡动画	 			*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_PlayerDeath(void)
{
	if(Remilia.Flag_Direction)
		Anime_PlayerDeathR();
	else
		Anime_PlayerDeathL();
}

/************************************/
/*函数名：Anime_PlayerDeathR		*/
/*功  能：玩家死亡动画	 			*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_PlayerDeathR(void)
{
	putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	putimage_withalpha(NULL,IMG_Remilia_Death_R,Remilia.x,Remilia.y-Anime_RemDeathOffset_Y,Anime_RemDeathPara_R1);
	delay_fps(Remilia_DeathSpeed);
	putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	putimage_withalpha(NULL,IMG_Remilia_Death_R,Remilia.x,Remilia.y-Anime_RemDeathOffset_Y,Anime_RemDeathPara_R2);
	delay_fps(Remilia_DeathSpeed);
	putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	putimage_withalpha(NULL,IMG_Remilia_Death_R,Remilia.x,Remilia.y-Anime_RemDeathOffset_Y,Anime_RemDeathPara_R3);
	delay_fps(Remilia_DeathSpeed);
	putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	putimage_withalpha(NULL,IMG_Remilia_Death_R,Remilia.x,Remilia.y-Anime_RemDeathOffset_Y,Anime_RemDeathPara_R4);
	delay_fps(Remilia_DeathSpeed);
	putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	putimage_withalpha(NULL,IMG_Remilia_Death_R,Remilia.x,Remilia.y-Anime_RemDeathOffset_Y,Anime_RemDeathPara_R5);
	delay_fps(Remilia_DeathSpeed);
}

/************************************/
/*函数名：Anime_PlayerDeathL		*/
/*功  能：玩家死亡动画	 			*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_PlayerDeathL(void)
{
	putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	putimage_withalpha(NULL,IMG_Remilia_Death_L,Remilia.x,Remilia.y-Anime_RemDeathOffset_Y,Anime_RemDeathPara_L1);
	delay_fps(Remilia_DeathSpeed);
	putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	putimage_withalpha(NULL,IMG_Remilia_Death_L,Remilia.x,Remilia.y-Anime_RemDeathOffset_Y,Anime_RemDeathPara_L2);
	delay_fps(Remilia_DeathSpeed);
	putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	putimage_withalpha(NULL,IMG_Remilia_Death_L,Remilia.x,Remilia.y-Anime_RemDeathOffset_Y,Anime_RemDeathPara_L3);
	delay_fps(Remilia_DeathSpeed);
	putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	putimage_withalpha(NULL,IMG_Remilia_Death_L,Remilia.x,Remilia.y-Anime_RemDeathOffset_Y,Anime_RemDeathPara_L4);
	delay_fps(Remilia_DeathSpeed);
	putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	putimage_withalpha(NULL,IMG_Remilia_Death_L,Remilia.x,Remilia.y-Anime_RemDeathOffset_Y,Anime_RemDeathPara_L5);
	delay_fps(Remilia_DeathSpeed);
}

/************************************/
/*函数名：Anime_PlayerMoveR			*/
/*功  能：水平动画	 				*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_PlayerMoveR(void)
{
	Anime_Offset_x = Remilia.x - Anime_RemMoveOffset_X;
	Anime_Offset_y = Remilia.y - Anime_RemMoveOffset_Y;
	
	if(Anime_MoveStand_FlagA>7)
			Anime_MoveStand_FlagA=0;		//重置

	putimage_withalpha(NULL,IMG_Remilia_Move_R[Anime_MoveStand_FlagA],Anime_Offset_x,Anime_Offset_y);
	
	if(Anime_MoveStand_FlagB==Anime_Move_Speed)
	{
		Anime_MoveStand_FlagB=0;
		Anime_MoveStand_FlagA++;		//换帧 	
	}
	
	Anime_MoveStand_FlagB++;
}

/************************************/
/*函数名：Anime_PlayerMoveL			*/
/*功  能：水平动画	 				*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_PlayerMoveL(void)
{
	Anime_Offset_x = Remilia.x - Anime_RemMoveOffset_X;
	Anime_Offset_y = Remilia.y - Anime_RemMoveOffset_Y;
	
	if(Anime_MoveStand_FlagA>8)
			Anime_MoveStand_FlagA=0;
	
	putimage_withalpha(NULL,IMG_Remilia_Move_L[Anime_MoveStand_FlagA],Anime_Offset_x,Anime_Offset_y);
	
	if(Anime_MoveStand_FlagB==Anime_Move_Speed)
	{
		Anime_MoveStand_FlagB=0;
		Anime_MoveStand_FlagA++;		//换帧 
	}
	
	Anime_MoveStand_FlagB++;
}

/************************************/
/*函数名：Anime_PlayerMove			*/
/*功  能：移动动画	 				*/
/*参  数：方向  0左  1右			*/
/*返回值： 		 					*/
/************************************/
void Anime_PlayerMove(bool Direction)
{
	if(!Remilia.Flag_Beaten)
	{
		if(Direction && Flag_isMoving)
			Anime_PlayerMoveR();
		else if(Flag_isMoving)
			Anime_PlayerMoveL();
		Flag_isMoving = 0;
	}
	
}

/************************************/
/*函数名：Anime_PlayerDefense		*/
/*功  能：防御动画	 				*/
/*参  数：方向  0左  1右			*/
/*返回值： 		 					*/
/************************************/
void Anime_PlayerDefense(bool Direction)
{
	if(Remilia.Defense && Direction)
	{
		Anime_PlayerDefense_R();
	}
	else if(Remilia.Defense)
	{
		Anime_PlayerDefense_L();
	}
}

/************************************/
/*函数名：Anime_PlayerDefense_R		*/
/*功  能：防御动画	 				*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_PlayerDefense_R(void)
{
	putimage_withalpha(NULL,IMG_Defense_R[DefenseFlag],Remilia.x-32,Remilia.y-32);
	
	if(DefenseCtr == Remilia_DefensSpeed)
	{
		if(DefenseFlag)
			DefenseFlag = 0;
		else
			DefenseFlag = 1;
		
		Remilia.MP--;
		DefenseCtr = 0;
	}
	DefenseCtr++;
}

/************************************/
/*函数名：Anime_PlayerDefense_L		*/
/*功  能：防御动画	 				*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_PlayerDefense_L(void)
{	
	putimage_withalpha(NULL,IMG_Defense_L[DefenseFlag],Remilia.x-32,Remilia.y-32);
	
	if(DefenseCtr == Remilia_DefensSpeed)
	{
		if(DefenseFlag)
			DefenseFlag = 0;
		else
			DefenseFlag = 1;
		
		Remilia.MP--;
		DefenseCtr = 0;
	}
	DefenseCtr++;
}

/************************************/
/*函数名：Anime_RemiliaStand_R		*/
/*功  能：攻击动画	 				*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_RemiliaStand_R(void)
{
	Anime_Offset_x = Remilia.x - Anime_RemStandOffset_X;
	Anime_Offset_y = Remilia.y - Anime_RemStandOffset_Y;
	
	if(Anime_MoveStand_FlagA>7)
			Anime_MoveStand_FlagA=0;
	
	putimage_withalpha(NULL,IMG_Remilia_Stand_R[Anime_MoveStand_FlagA],Anime_Offset_x,Anime_Offset_y);
	
	if(Anime_MoveStand_FlagB==Anime_Move_Speed)
	{
		Anime_MoveStand_FlagB=0;
		Anime_MoveStand_FlagA++;		//换帧 
	}
	
	Anime_MoveStand_FlagB++;
}

/************************************/
/*函数名：Anime_RemiliaStand_L		*/
/*功  能：攻击动画	 				*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_RemiliaStand_L(void)
{
	Anime_Offset_x = Remilia.x - Anime_RemStandOffset_X;
	Anime_Offset_y = Remilia.y - Anime_RemStandOffset_Y;
	
	if(Anime_MoveStand_FlagA>7)
			Anime_MoveStand_FlagA=0;
	
	putimage_withalpha(NULL,IMG_Remilia_Stand_L[Anime_MoveStand_FlagA],Anime_Offset_x,Anime_Offset_y);
	
	if(Anime_MoveStand_FlagB==Anime_Move_Speed)
	{
		Anime_MoveStand_FlagB=0;
		Anime_MoveStand_FlagA++;		//换帧 
	}
	
	Anime_MoveStand_FlagB++;
}

/************************************/
/*函数名：Anime_PlayerStand			*/
/*功  能：站立动画	 				*/
/*参  数：方向  0左  1右			*/
/*返回值： 		 					*/
/************************************/
void Anime_PlayerStand(bool Direction)
{
	if(!Remilia.Flag_Beaten)
	{
		if(Direction && !Flag_isMoving)
		{
			Anime_RemiliaStand_R();
			Flag_isMoving = 0;
		}	
		else if(!Flag_isMoving)
		{
			Anime_RemiliaStand_L();
			Flag_isMoving = 0;
		}
	}
}

/************************************/
/*函数名：Anime_RemBeaten_L			*/
/*功  能：被攻击动画	 			*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemBeaten_L(void)
{
	if(Anime_BeatenCtrA > 4)
		Anime_BeatenCtrA = 1;
		
	switch(Anime_BeatenCtrA)
	{
		case 1:
			putimage_withalpha(NULL,IMG_Remilia_Beaten_L,Remilia.x-Anime_RemBeatOffset_LX,Remilia.y-Anime_RemBeatOffset_Y,Anime_RemBeatenPara_L1);
			if(Music_Beaten[BeatMusRand].GetPlayStatus() == MUSIC_MODE_STOP && !Flag_isSkilling)
			{
				BeatMusRand = random(3);
				Music_Beaten[BeatMusRand].Play(0);
			}
			break;
		case 2:
			putimage_withalpha(NULL,IMG_Remilia_Beaten_L,Remilia.x-Anime_RemBeatOffset_LX,Remilia.y-Anime_RemBeatOffset_Y,Anime_RemBeatenPara_L2);
			break;
		case 3:
			putimage_withalpha(NULL,IMG_Remilia_Beaten_L,Remilia.x-Anime_RemBeatOffset_LX,Remilia.y-Anime_RemBeatOffset_Y,Anime_RemBeatenPara_L3);
			break;
		case 4:
			putimage_withalpha(NULL,IMG_Remilia_Beaten_L,Remilia.x-Anime_RemBeatOffset_LX,Remilia.y-Anime_RemBeatOffset_Y,Anime_RemBeatenPara_L4);
			Remilia.Flag_Beaten = 0;
			Anime_BeatenCtrA = 1;
			Anime_BeatenCtrB = 0;
			break;
	}
	
	if(Anime_BeatenCtrB == Remilia_BeatenSpeed)
	{
		Anime_BeatenCtrB = 0;
		Anime_BeatenCtrA++;
	}
	Anime_BeatenCtrB++;
}

/************************************/
/*函数名：Anime_RemBeaten_R			*/
/*功  能：被攻击动画	 			*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemBeaten_R(void)
{
	switch(Anime_BeatenCtrA)
	{
		case 1:
			putimage_withalpha(NULL,IMG_Remilia_Beaten_R,Remilia.x-Anime_RemBeatOffset_RX,Remilia.y-Anime_RemBeatOffset_Y,Anime_RemBeatenPara_R1);
			if(Music_Beaten[BeatMusRand].GetPlayStatus() == MUSIC_MODE_STOP && !Flag_isSkilling)
			{
				BeatMusRand = random(3);
				Music_Beaten[BeatMusRand].Play(0);
			}
			break;
		case 2:
			putimage_withalpha(NULL,IMG_Remilia_Beaten_R,Remilia.x-Anime_RemBeatOffset_RX,Remilia.y-Anime_RemBeatOffset_Y,Anime_RemBeatenPara_R2);
			break;
		case 3:
			putimage_withalpha(NULL,IMG_Remilia_Beaten_R,Remilia.x-Anime_RemBeatOffset_RX,Remilia.y-Anime_RemBeatOffset_Y,Anime_RemBeatenPara_R3);
			break;
		case 4:
			putimage_withalpha(NULL,IMG_Remilia_Beaten_R,Remilia.x-Anime_RemBeatOffset_RX,Remilia.y-Anime_RemBeatOffset_Y,Anime_RemBeatenPara_R4);
			Remilia.Flag_Beaten = 0;
			Anime_BeatenCtrA = 1;
			Anime_BeatenCtrB = 0;
			break;
	}
	
	if(Anime_BeatenCtrB == Remilia_BeatenSpeed)
	{
		Anime_BeatenCtrB = 0;
		Anime_BeatenCtrA++;
	}
	Anime_BeatenCtrB++;
	
}


/************************************/
/*函数名：Anime_RemBeaten			*/
/*功  能：被攻击动画	 			*/
/*参  数：方向  0左  1右			*/
/*返回值： 		 					*/
/************************************/
void Anime_RemBeaten(bool Direction)
{
	if(Remilia.Flag_Beaten && Direction)
	{
		Anime_RemBeaten_R();
	}
	else if(Remilia.Flag_Beaten)
	{
		Anime_RemBeaten_L();
	}
}

/************************************/
/*函数名： Process_PlayerDamage		/
/*功  能： 技能对敌伤害			 	*/
/*参  数： 处理页数，技能结构体		*/
/*返回值：							*/
/************************************/
void Process_PlayerDamage(int page,Object_Parameter Skill)
{
	int i,Offset_X,Offset_Y;
	
	randomize();
	switch(Skill.type)
	{
		case 1:
			Offset_X = Skill.x + SkillA_DamRangeOff_X;
			Offset_Y = Skill.y + SkillA_DamRangeOff_Y;
			break;
		case 2:
			Offset_X = Skill.x + SkillB_DamRangeOff_X;
			Offset_Y = Skill.y + SkillB_DamRangeOff_Y;
			break;
		case 31:
		case 32:
			Offset_X = Skill.x;
			Offset_Y = Skill.y;
			break;
		case 33:
			Offset_X = Skill.x + NorAtk_DamRangeOff_X;
			Offset_Y = Skill.y + NorAtk_DamRangeOff_Y;
			break;
	}

	for(i=0;i<Page_EnemyTypeAmount[page][0];i++)
	{
		if(!MapData_Enemy[page][i].Flag_HitEffect && !MapData_Enemy[page][i].Flag_Death)
			if(Offset_X+Skill.Length>MapData_Enemy[page][i].x)
				if(Offset_X<MapData_Enemy[page][i].x+MapData_Enemy[page][i].Length)
					if(Offset_Y+Skill.Width>MapData_Enemy[page][i].y)
						if(Offset_Y<MapData_Enemy[page][i].y+MapData_Enemy[page][i].Width)
						{
							
							switch(Skill.type)
							{
								case 1:
									Skill.Damage = random(100)-50+SkillA_Damage;
									Remilia_Skill_A.Damage = Skill.Damage;
									break;
								case 2:
									Skill.Damage = random(100)-50+SkillB_Damage;
									Remilia_Skill_B.Damage = Skill.Damage;
									break;
								case 31:
									Skill.Damage = random(100)-50+NorAtk_Damage_A;
									Remilia_NorAtk_A.Damage = Skill.Damage;
									break;
								case 32:
									Skill.Damage = random(100)-50+NorAtk_Damage_B;
									Remilia_NorAtk_B.Damage = Skill.Damage;
									break;
								case 33:
									Skill.Damage = random(100)-50+NorAtk_Damage_C;
									Remilia_NorAtk_C.Damage = Skill.Damage;
									break;
							}
							
							MapData_Enemy[page][i].HP -= Skill.Damage;
							MapData_Enemy[page][i].Flag_HitEffect = Skill.type;
							
							if(MapData_Enemy[page][i].HP <= 0)
							{
								MapData_Enemy[page][i].Flag_Death = 1;
								MapData_Enemy[page][i].DeathEffect_Ctr = 0;
								if(MapData_Enemy[page][i].type == 12)
									MapData_Enemy[page][i].Flag_Direction = 1;
							}
						}
	}
	
	#ifdef ENABLE_Aux_Frame
	line( Offset_X, Offset_Y, Offset_X + Skill.Length, Offset_Y);
	line( Offset_X, Offset_Y + Skill.Width, Offset_X + Skill.Length, Offset_Y + Skill.Width);
	line( Offset_X, Offset_Y, Offset_X, Offset_Y + Skill.Width);
	line( Offset_X + Skill.Length, Offset_Y, Offset_X + Skill.Length, Offset_Y + Skill.Width);
	#endif
}

/************************************/
/*函数名： Process_PDamageBoss		*/
/*功  能： 技能对敌伤害(Boss关卡)	*/
/*参  数： 技能结构体				*/
/*返回值：							*/
/************************************/
void Process_PDamageBoss(Object_Parameter Skill)
{
	int i,Offset_X,Offset_Y;
	
	randomize();
	switch(Skill.type)
	{
		case 1:
			Offset_X = Skill.x + SkillA_DamRangeOff_X;
			Offset_Y = Skill.y + SkillA_DamRangeOff_Y;
			break;
		case 2:
			Offset_X = Skill.x + SkillB_DamRangeOff_X;
			Offset_Y = Skill.y + SkillB_DamRangeOff_Y;
			break;
		case 31:
		case 32:
			Offset_X = Skill.x;
			Offset_Y = Skill.y;
			break;
		case 33:
			Offset_X = Skill.x + NorAtk_DamRangeOff_X;
			Offset_Y = Skill.y + NorAtk_DamRangeOff_Y;
			break;
	}
	
	if(!Boss.Flag_HitEffect && !Boss.Flag_Death)
		if(Offset_X + Skill.Length > Boss.x)
			if(Offset_X < Boss.x + Boss.Length)
				if(Offset_Y + Skill.Width > Boss.y)
					if(Offset_Y < Boss.y + Boss.Width)
					{
						switch(Skill.type)
						{
							case 1:
								Skill.Damage = random(100)-50+SkillA_Damage;
								Remilia_Skill_A.Damage = Skill.Damage;
								break;
							case 2:
								Skill.Damage = random(100)-50+SkillB_Damage;
								Remilia_Skill_B.Damage = Skill.Damage;
								break;
							case 31:
								Skill.Damage = random(100)-50+NorAtk_Damage_A;
								Remilia_NorAtk_A.Damage = Skill.Damage;
								break;
							case 32:
								Skill.Damage = random(100)-50+NorAtk_Damage_B;
								Remilia_NorAtk_B.Damage = Skill.Damage;
								break;
							case 33:
								Skill.Damage = random(100)-50+NorAtk_Damage_C;
								Remilia_NorAtk_C.Damage = Skill.Damage;
								break;
						}
						
						Boss.HP -= Skill.Damage;
						Boss.Flag_HitEffect = Skill.type;
						
						if(Boss.HP <= 0)
						{
							Boss.Flag_Death = 1;
							Boss.DeathEffect_Ctr = 0;
						}
					}

	#ifdef ENABLE_Aux_Frame
	line( Offset_X, Offset_Y, Offset_X + Skill.Length, Offset_Y);
	line( Offset_X, Offset_Y + Skill.Width, Offset_X + Skill.Length, Offset_Y + Skill.Width);
	line( Offset_X, Offset_Y, Offset_X, Offset_Y + Skill.Width);
	line( Offset_X + Skill.Length, Offset_Y, Offset_X + Skill.Length, Offset_Y + Skill.Width);
	#endif
}

/************************************/
/*函数名： Player_SkillDamage		*/
/*功  能： 技能对敌伤害			 	*/
/*参  数： 技能结构体			 	*/
/*返回值：							*/
/************************************/
void Player_SkillDamage(Object_Parameter Skill)
{
	if(!isBossStage)
	{
		Process_PlayerDamage(Current_Page,Skill);
		
		if(Current_Page!=Page_Amount-1)
			Process_PlayerDamage(Current_Page+1,Skill);
			
		if(Current_Page!=0)
			Process_PlayerDamage(Current_Page-1,Skill);
	}
	else
	{
		Process_PDamageBoss(Skill);
	}
}

/************************************/
/*函数名：Anime_RemSkill_HitEffect	*/
/*功  能：技能命中效果				*/
/*参  数：处理页数					*/
/*返回值： 		 					*/
/************************************/
void Anime_RemSkill_HitEffect(int page)
{
	int i,j,OffsetX,OffsetY;
	char c_temp[10] = "-";
	
	setfont(40,0,"DFGFuun-W7",0,0,FW_BLACK,0,0,0);
	for(i=0;i<Page_EnemyTypeAmount[page][0];i++)
	{
		if(MapData_Enemy[page][i].Flag_HitEffect && MapData_Enemy[page][i].type!=12)
		{
			OffsetX = MapData_Enemy[page][i].x - Anime_SkillBHitEffect_Offset_X;
			OffsetY = MapData_Enemy[page][i].y - Anime_SkillBHitEffect_Offset_Y;
			
			switch(MapData_Enemy[page][i].Flag_HitEffect)
			{
				case 1:
					sprintf(String,"%d",Remilia_Skill_A.Damage);
					break;
				case 2:
					sprintf(String,"%d",Remilia_Skill_B.Damage);
					break;
				case 31:
					sprintf(String,"%d",Remilia_NorAtk_A.Damage);
					break;
				case 32:
					sprintf(String,"%d",Remilia_NorAtk_B.Damage);
					break;
				case 33:
					sprintf(String,"%d",Remilia_NorAtk_C.Damage);
					break;
				default:
					goto lable;
			}
			
			if(MapData_Enemy[page][i].type == 10)
				setcolor(0x00F5FF);
			if(MapData_Enemy[page][i].type == 11)
				setcolor(0xFF00FF);
			
			strcat(c_temp,String);
			outtextxy(MapData_Enemy[page][i].x - 20,MapData_Enemy[page][i].y - MapData_Enemy[page][i].HitEffect_Ctr * 6,c_temp);
			
			lable:;
			
			switch(MapData_Enemy[page][i].HitEffect_Ctr)
			{
				case 1:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_1);
					break;
				case 2:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_2);
					break;
				case 3:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_3);
					break;
				case 4:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_4);
					break;
				case 5:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_5);
					break;
				case 6:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_6);
					break;
				case 7:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_7);
					break;
				case 8:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_8);
					break;
				case 9:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_9);
					break;
				case 10:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_10);
					break;
				case 11:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_11);
					break;
				case 12:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_12);
					break;
				case 13:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_13);
					break;
				case 14:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_14);
					break;
				case 15:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_15);
					break;
				case 16:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_16);
					break;
				case 17:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_17);
					break;
				case 18:
					putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_18);
					MapData_Enemy[page][i].HitEffect_Ctr = 1;
					MapData_Enemy[page][i].Flag_HitEffect = 0;
					break;
			}

			if(Anime_SkillBHitEffect_Flag == Anime_SkillHitEffect_Speed)
			{
				Anime_SkillBHitEffect_Flag = 0;
				for(j=0;j<Page_EnemyTypeAmount[page][0];j++)
				{
					if(MapData_Enemy[page][j].Flag_HitEffect)
						MapData_Enemy[page][j].HitEffect_Ctr++;
				}
			}
			Anime_SkillBHitEffect_Flag++;
		}
	}
}

/************************************/
/*函数名：Anime_RemSkill_HitBoss	*/
/*功  能：技能命中效果				*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemSkill_HitBoss(void)
{
	int OffsetX,OffsetY,i;
	char c_temp[10] = "-";
	
	setfont(50,0,"DFGFuun-W7",0,0,FW_BLACK,0,0,0);
	setcolor(0x00F5FF);
	if(Boss.Flag_HitEffect)
	{
		OffsetX = Boss.x + Anime_BossHitEffect_Offset_X;
		OffsetY = Boss.y + Anime_BossHitEffect_Offset_Y;
		
		switch(Boss.Flag_HitEffect)
		{
			case 1:
				sprintf(String,"%d",Remilia_Skill_A.Damage);
				break;
			case 2:
				sprintf(String,"%d",Remilia_Skill_B.Damage);
				break;
			case 31:
				sprintf(String,"%d",Remilia_NorAtk_A.Damage);
				break;
			case 32:
				sprintf(String,"%d",Remilia_NorAtk_B.Damage);
				break;
			case 33:
				sprintf(String,"%d",Remilia_NorAtk_C.Damage);
				break;
			default:
				goto lable;
		}
		
		strcat(c_temp,String);
		outtextxy(Boss.x + 20,Boss.y - Boss.HitEffect_Ctr * 6,c_temp);

		lable:;

		switch(Boss.HitEffect_Ctr)
		{
			case 1:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_1);
				break;
			case 2:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_2);
				break;
			case 3:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_3);
				break;
			case 4:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_4);
				break;
			case 5:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_5);
				break;
			case 6:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_6);
				break;
			case 7:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_7);
				break;
			case 8:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_8);
				break;
			case 9:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_9);
				break;
			case 10:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_10);
				break;
			case 11:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_11);
				break;
			case 12:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_12);
				break;
			case 13:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_13);
				break;
			case 14:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_14);
				break;
			case 15:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_15);
				break;
			case 16:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_16);
				break;
			case 17:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_17);
				break;
			case 18:
				putimage_withalpha(NULL,IMG_RemSkillB_HitEffect,OffsetX,OffsetY,Anime_RemSkillB_HitEffect_18);
				Boss.HitEffect_Ctr = 1;
				Boss.Flag_HitEffect = 0;
				break;
		}
	
		if(Anime_SkillBHitEffect_Flag == Anime_SkillHitEffect_Speed)
		{
			Anime_SkillBHitEffect_Flag = 0;
			if(Boss.Flag_HitEffect)
					Boss.HitEffect_Ctr++;
		}
		Anime_SkillBHitEffect_Flag++;
	}
}

/************************************/
/*函数名：Process_RemSkill_HitEffect*/
/*功  能：被攻击效果				*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Process_RemSkill_HitEffect(void)
{
	
	Anime_RemSkill_HitEffect(Current_Page);
	
	if(Current_Page!=Page_Amount-1)
		Anime_RemSkill_HitEffect(Current_Page+1);
		
	if(Current_Page!=0)
		Anime_RemSkill_HitEffect(Current_Page-1);
}

/************************************/
/*函数名： Process_BarrageDamage	*/
/*功  能： 弹幕对敌伤害			 	*/
/*参  数： 处理页数，技能结构体		*/
/*返回值：							*/
/************************************/
void Process_BarrageDamage(int page,Barrage_Parameter* barrage1,Barrage_Parameter* barrage2)
{
	#define BARRAGE_RANGE_CHECK_1 barrage1->x + 16 > MapData_Enemy[page][i].x && barrage1->x + 16 < MapData_Enemy[page][i].x + MapData_Enemy[page][i].Length \
							   && barrage1->y + 16 > MapData_Enemy[page][i].y && barrage1->y + 16 < MapData_Enemy[page][i].y + MapData_Enemy[page][i].Width
	#define BARRAGE_RANGE_CHECK_2 barrage2->x + 16 > MapData_Enemy[page][i].x && barrage2->x + 16 < MapData_Enemy[page][i].x + MapData_Enemy[page][i].Length \
							   && barrage2->y + 16 > MapData_Enemy[page][i].y && barrage2->y + 16 < MapData_Enemy[page][i].y + MapData_Enemy[page][i].Width
	#define PROCESS MapData_Enemy[page][i].HP -= SkillBarrage_Damage; 		     \
					MapData_Enemy[page][i].Flag_HitEffect = SkillBarrage_Type;	 \
																				 \
					if(MapData_Enemy[page][i].HP <= 0)							 \
					{ 															 \
						MapData_Enemy[page][i].Flag_Death = 1; 					 \
						MapData_Enemy[page][i].DeathEffect_Ctr = 0; 			 \
																				 \
						if(MapData_Enemy[page][i].type == 12) 					 \
							MapData_Enemy[page][i].Flag_Direction = 1; 			 \
					}
	int i;
	
	for(i=0;i<Page_EnemyTypeAmount[page][0];i++)
	{
		if(!MapData_Enemy[page][i].Flag_Death)
		{
			if(!barrage1->flag && BARRAGE_RANGE_CHECK_1)
			{
				barrage1->flag = 1;
				PROCESS
			}
			else if(!barrage2->flag && BARRAGE_RANGE_CHECK_2)
			{
				barrage2->flag = 1;
				PROCESS
			}
		}
	}
	
	#undef BARRAGE_COLLISION_CHECK_1
	#undef BARRAGE_COLLISION_CHECK_2
	#undef PROCESS
}

/************************************/
/*函数名： Process_BarrageDamageBoss*/
/*功  能： 弹幕对BOSS伤害			*/
/*参  数： 处理页数，技能结构体		*/
/*返回值：							*/
/************************************/
void Process_BarrageDamageBoss(Barrage_Parameter* barrage1, Barrage_Parameter* barrage2)
{
	#define PROCESS Boss.HP -= SkillBarrage_Damage;				\
					Boss.Flag_HitEffect = SkillBarrage_Type;	\
																\
					if(Boss.HP <= 0)							\
					{											\
						Boss.Flag_Death = 1;					\
						Boss.DeathEffect_Ctr = 0;				\
					}
	int i;

	if(!Boss.Flag_Death)
	{
		if(!barrage1->flag && barrage1->x + 16 > Boss.x && barrage1->x + 16 < Boss.x + Boss.Length && barrage1->y + 16 > Boss.y && barrage1->y + 16 < Boss.y + Boss.Width)
		{
			barrage1->flag = 1;
			PROCESS
		}
		else if(!barrage2->flag && barrage2->x + 16 > Boss.x && barrage2->x + 16 < Boss.x + Boss.Length && barrage2->y + 16 > Boss.y && barrage2->y + 16 < Boss.y + Boss.Width)
		{
			barrage2->flag = 1;
			PROCESS
		}
	}
	#undef PROCESS
}

/************************************/
/*函数名： Player_BarrageDamage		*/
/*功  能： 弹幕对敌伤害			 	*/
/*参  数： 弹幕结构体			 	*/
/*返回值：							*/
/************************************/
void Player_BarrageDamage(Barrage_Parameter* barrage1,Barrage_Parameter* barrage2)
{
	if(!isBossStage)
	{
		Process_BarrageDamage(Current_Page,barrage1,barrage2);
		
		if(Current_Page!=Page_Amount-1)
			Process_BarrageDamage(Current_Page+1,barrage1,barrage2);
			
		if(Current_Page!=0)
			Process_BarrageDamage(Current_Page-1,barrage1,barrage2);
	}
	else
	{
		Process_BarrageDamageBoss(barrage1,barrage2);
	}
}

/************************************/
/*函数名：Process_Remilia_Barrage	*/
/*功  能：大招		 				*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Process_Remilia_Barrage(void)
{
	if(Remilia.Flag_Barrage)
	{
		//上升阶段 
		if(Remilia.y != Barrage_Height)
		{
			if(Remilia.y > Barrage_Height)
			{
				if(Check_TopBlock(-1,Current_Page))
					Barrage_Height = Remilia.y;
				Remilia.y-=1;
			}
			if(Remilia.y < Barrage_Height)
			{
				if(Check_BelowBlock(-1,Current_Page))
					Barrage_Height = Remilia.y;
				Remilia.y+=1;
			}
				
			Anime_PlayerStand(1);
		}
		else
		{	
			if(Barrage_ActCtr > 15)//释放阶段 
			{
				putimage_withalpha(NULL,IMG_Remilia_Start[9],Remilia.x -96 ,Remilia.y -96 );
				RemiliaSkill_Barrage();
				putimage_withalpha(NULL,IMG_Remilia_BarrageAct[2],Remilia.x - 36,Remilia.y - 24);
			}
			else//动作阶段 
			{
				if(Barrage_ActCtr > 9)
					putimage_withalpha(NULL,IMG_Remilia_Start[9],Remilia.x -96 ,Remilia.y -96 );
				else
					putimage_withalpha(NULL,IMG_Remilia_Start[Barrage_ActCtr],Remilia.x -96 ,Remilia.y -96 );
				
				if(Barrage_ActCtr > 2)
				{
					if(Music_RemBarrage.GetPlayStatus() == MUSIC_MODE_STOP)
						Music_RemBarrage.Play(0);
					putimage_withalpha(NULL,IMG_Remilia_BarrageAct[2],Remilia.x - 36,Remilia.y - 24);
				}
				else
					putimage_withalpha(NULL,IMG_Remilia_BarrageAct[Barrage_ActCtr],Remilia.x - 36,Remilia.y - 24);
				
				if(Barrage_Speed_Ctr == SkillBarrage_ActSpeed)
				{
					Barrage_Speed_Ctr = 0;
					Barrage_ActCtr++;
				}
				Barrage_Speed_Ctr++;
			}
		}
	}
}

/************************************/
/*函数名：RemiliaSkill_Barrage		*/
/*功  能：Remilia弹幕技能		 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void RemiliaSkill_Barrage(void)
{
	int i;
	float damage;
	float temp;
	
	if(Barrage_Flag == -1)
	{
		RemiliaSkill_Barrage_Init();
	}
	Barrage_Flag = 0;

	for(i=0;i<Barrage_Ctr_A;i++)
	{
		if(!RemBarrage_1[i].flag || !RemBarrage_2[i].flag)
		{
			Barrage_Flag = 1;
			
			//加速度控制 
			if(!Barrage_Speed_Ctr)
			{	
				temp = 7 - sqrt(RemBarrage_1[i].rad / 70);
				if(temp < 1)
					temp = 1;
				RemBarrage_1[i].rad += temp;
				RemBarrage_2[i].rad += temp;
				//坐标计算 
				Math_RotateAxis(&RemBarrage_1[i],1);
				Math_RotateAxis(&RemBarrage_2[i],1);

				//出界检测 
				if(RemBarrage_1[i].x < -20 || RemBarrage_1[i].y > 680 || RemBarrage_1[i].y < -20 || RemBarrage_1[i].x > 1020)
					RemBarrage_1[i].flag = 1;
				if(RemBarrage_2[i].x < -20 || RemBarrage_2[i].y > 680 || RemBarrage_2[i].y < -20 || RemBarrage_2[i].x > 1020)
					RemBarrage_2[i].flag = 1;
					
				//碰撞检测 
				Player_BarrageDamage(&RemBarrage_1[i],&RemBarrage_2[i]);
			}
			//释放弹幕
			if(!RemBarrage_1[i].flag)
			{
				if(Music_BossBarrageFire.GetPlayStatus() == MUSIC_MODE_STOP)
					Music_BossBarrageFire.Play(0);
				putimage_withalpha(NULL,IMG_Remilia_Barrage[RemBarrage_1[i].type],RemBarrage_1[i].x,RemBarrage_1[i].y);
			}
			if(!RemBarrage_2[i].flag)
			{
				if(Music_BossBarrageFire.GetPlayStatus() == MUSIC_MODE_STOP)
					Music_BossBarrageFire.Play(0);
				putimage_withalpha(NULL,IMG_Remilia_Barrage[RemBarrage_2[i].type],RemBarrage_2[i].x,RemBarrage_2[i].y);
			}
		}
	}

	//释放结束 
	if(!Barrage_Flag)
	{
		Barrage_Height = SkillBarrage_Height;
		Barrage_ActCtr = 0;
		Barrage_Flag = -1;
		Barrage_Ctr_A = 0;
		Barrage_Ctr_B = 0;
		Flag_isSkilling = 0;
		Remilia.Flag_Barrage = 0;
	}

	//间隔计数器处理 
	if(Barrage_Ctr_B == SkillBarrage_RadGap)
	{
		if(Barrage_Ctr_A < SkillBarrage_Density)
		{
			Barrage_Ctr_A++;
		}
		Barrage_Ctr_B = 0;
	}
	Barrage_Ctr_B++;
	//速度计数器处理 
	if(Barrage_Speed_Ctr > 0)
		Barrage_Speed_Ctr--;
	else
		Barrage_Speed_Ctr = SkillBarrage_Speed;
}

/************************************/
/*函数名：RemiliaSkill_Barrage_Init	*/
/*功  能：初始化弹幕			 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void RemiliaSkill_Barrage_Init(void)
{
	int i = 0, j = 0, z = 0;
	bool Direction_A = 0, Direction_B = 0;

	//初始化弹幕序列
	for(i=0;i<SkillBarrage_Density;i++)
	{
		randomize();
		
		RemBarrage_1[i].arc = j * (AngleToArc_Value * SkillBarrage_AngGap);//初始化角度
		RemBarrage_1[i].rad = 0;
		RemBarrage_1[i].flag = 0;
		RemBarrage_1[i].type = random(7);
		
		RemBarrage_2[i].arc = z * (AngleToArc_Value * SkillBarrage_AngGap);//初始化角度
		RemBarrage_2[i].rad = 0;
		RemBarrage_2[i].flag = 0;
		RemBarrage_2[i].type = random(7);
		
		j++;
		z--;
		
		//初始角处理 
		if(j > SkillBarrage_AngEnd / SkillBarrage_AngGap)
		{
			j = 0;
			z = 0;
		}
		
		//坐标计算 
		Math_RotateAxis(&RemBarrage_1[i],1);
		Math_RotateAxis(&RemBarrage_2[i],1);
	}
	
	Barrage_Ctr_A = 1;
	Barrage_Ctr_B = 1;
	Barrage_Flag = 1;
}

/************************************/
/*函数名：Anime_RemiliaSkill_B		*/
/*功  能：技能B起始动画	 			*/
/*参  数：方向  0左  1右			*/
/*返回值： 		 					*/
/************************************/
void Anime_RemiliaSkill_B(bool Direction)
{
	if(Direction && Remilia.Flag_Skilling_B)
		Anime_RemiliaSkill_BR();
	else if(Remilia.Flag_Skilling_B)
		Anime_RemiliaSkill_BL();
}

/************************************/
/*函数名：Anime_RemiliaSkill_BR		*/
/*功  能：攻击动画	 				*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_RemiliaSkill_BR(void)
{
	if(Anime_SkillB_FlagA == 0)
		Music_RemSkill_B_Start.Play(100,2000);
	
	Remilia_Skill_B.x = Remilia.x - Anime_RemSkillBOffset_X;
	Remilia_Skill_B.y = Remilia.y - Anime_RemSkillBOffset_Y;
	
	putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[Anime_SkillB_FlagA],Remilia_Skill_B.x,Remilia_Skill_B.y);
	
	Remilia_Skill_B.x += Anime_SkillB_RightXoffset;
	Remilia_Skill_B.y -= Anime_RemSkillBOffset_Effect_Y;
	
	switch(Anime_SkillB_FlagA)
	{
		case 3:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[11],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[12],Remilia_Skill_B.x,Remilia_Skill_B.y);
			Remilia_Skill_B.Flag_Direction = 1;
			break;
		case 4:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[13],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[14],Remilia_Skill_B.x,Remilia_Skill_B.y);
			break;
		case 5:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[15],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[16],Remilia_Skill_B.x,Remilia_Skill_B.y);
			break;
		case 6:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[17],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[18],Remilia_Skill_B.x,Remilia_Skill_B.y);
			break;
		case 7:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[19],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[20],Remilia_Skill_B.x,Remilia_Skill_B.y);
			break;
		case 8:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[21],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[22],Remilia_Skill_B.x,Remilia_Skill_B.y);
			break;
		case 9:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[23],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BR[24],Remilia_Skill_B.x,Remilia_Skill_B.y);
			break;
		case 10:
			//参数初始化 
			Music_RemSkill_B_Flying.Play(500,2300);
			Flag_isSkilling = 0;
			Remilia.Flag_Skilling_B = 0;
			Flag_SkillArrow_B = 1;
			Anime_SkillB_FlagA = 0;
			Anime_SkillB_FlagB = 0;
			break;
	}

	if(Anime_SkillB_FlagB == Anime_SkillB_Speed)
	{
		Anime_SkillB_FlagB = 0;
		Anime_SkillB_FlagA++;		//换帧 
	}
	Anime_SkillB_FlagB++;
}

/************************************/
/*函数名：Anime_RemSkillBArrow_R*/
/*功  能：技能B射出动画	 			*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_RemSkillBArrow_R(void)
{
	Remilia_Skill_B.x += Anime_SkillBArrow_XGap;
	
	Player_SkillDamage(Remilia_Skill_B);
	
	if(Anime_SkillBArrow_FlagA<20)
		putimage_withalpha(NULL,IMG_Remilia_SkillArrow_BR[Anime_SkillBArrow_FlagA],Remilia_Skill_B.x,Remilia_Skill_B.y);
	else 
	{	
		putimage_withalpha(NULL,IMG_Remilia_SkillArrow_BR[19],Remilia_Skill_B.x,Remilia_Skill_B.y);
		if(Anime_SkillBArrow_FlagA>30)
		{
			Anime_SkillBArrow_FlagB = 0;
			Anime_SkillBArrow_FlagA = 0;
			Flag_SkillArrow_B = 0;
		}
	}

	if(Anime_SkillBArrow_FlagB == Anime_SkillBArrow_Speed)
	{
		Anime_SkillBArrow_FlagB = 0;
		Anime_SkillBArrow_FlagA++;		//换帧 
	}
	Anime_SkillBArrow_FlagB++;
}

/************************************/
/*函数名：Anime_RemiliaSkill_BL		*/
/*功  能：攻击动画	 				*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_RemiliaSkill_BL(void)
{	
	if(Anime_SkillB_FlagA == 0)
		Music_RemSkill_B_Start.Play(100,2000);
	
	Remilia_Skill_B.x = Remilia.x - Anime_RemSkillBOffset_X;
	Remilia_Skill_B.y = Remilia.y - Anime_RemSkillBOffset_Y;
	
	putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[Anime_SkillB_FlagA],Remilia_Skill_B.x,Remilia_Skill_B.y);
	
	Remilia_Skill_B.x -= Anime_SkillB_LeftXoffset;
	Remilia_Skill_B.y -= Anime_RemSkillBOffset_Effect_Y;
	
	//技能效果 
	switch(Anime_SkillB_FlagA)
	{
		case 3:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[11],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[12],Remilia_Skill_B.x,Remilia_Skill_B.y);
			Remilia_Skill_B.Flag_Direction = 0;
			break;
		case 4:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[13],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[14],Remilia_Skill_B.x,Remilia_Skill_B.y);
			break;
		case 5:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[15],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[16],Remilia_Skill_B.x,Remilia_Skill_B.y);
			break;
		case 6:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[17],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[18],Remilia_Skill_B.x,Remilia_Skill_B.y);
			break;
		case 7:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[19],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[20],Remilia_Skill_B.x,Remilia_Skill_B.y);
			break;
		case 8:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[21],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[22],Remilia_Skill_B.x,Remilia_Skill_B.y);
			break;
		case 9:
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[23],Remilia_Skill_B.x,Remilia_Skill_B.y);
			putimage_withalpha(NULL,IMG_Remilia_SkillStart_BL[24],Remilia_Skill_B.x,Remilia_Skill_B.y);
			break;
		case 10:
			Flag_isSkilling = 0;
			Remilia.Flag_Skilling_B = 0;
			Flag_SkillArrow_B = 1;
			Anime_SkillB_FlagA = 0;
			Anime_SkillB_FlagB = 0;
			Music_RemSkill_B_Flying.Play(500,2300);
			break;
	}

	if(Anime_SkillB_FlagB == Anime_SkillB_Speed)
	{
		Anime_SkillB_FlagB = 0;
		Anime_SkillB_FlagA++;		//换帧 
	}
	Anime_SkillB_FlagB++;
}

/************************************/
/*函数名：Anime_RemSkillBArrow_L*/
/*功  能：技能B射出动画	 			*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_RemSkillBArrow_L(void)
{
	Remilia_Skill_B.x -= Anime_SkillBArrow_XGap;
		
	Player_SkillDamage(Remilia_Skill_B);	
		
	if(Anime_SkillBArrow_FlagA<20)
		putimage_withalpha(NULL,IMG_Remilia_SkillArrow_BL[Anime_SkillBArrow_FlagA],Remilia_Skill_B.x,Remilia_Skill_B.y);
	else 
	{	
		putimage_withalpha(NULL,IMG_Remilia_SkillArrow_BL[19],Remilia_Skill_B.x,Remilia_Skill_B.y);
		if(Anime_SkillBArrow_FlagA>30)
		{
			Anime_SkillBArrow_FlagB = 0;
			Anime_SkillBArrow_FlagA = 0;
			Flag_SkillArrow_B = 0;
		}
	}

	if(Anime_SkillBArrow_FlagB == Anime_SkillBArrow_Speed)
	{
		Anime_SkillBArrow_FlagB = 0;
		Anime_SkillBArrow_FlagA++;		//换帧 
	}
	Anime_SkillBArrow_FlagB++;
}

/************************************/
/*函数名：Anime_RemSkillBArrow	*/
/*功  能：技能B射出动画	 			*/
/*参  数：方向  0左  1右			*/
/*返回值： 		 					*/
/************************************/
void Anime_RemSkillBArrow(bool Direction)
{
	if(Flag_SkillArrow_B && Direction)
		Anime_RemSkillBArrow_R();
	else if(Flag_SkillArrow_B)
		Anime_RemSkillBArrow_L();	
}
/************************************/
/*函数名：Anime_RemiliaSkill_AR*/
/*功  能：攻击动画	 				*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_RemiliaSkill_AR(void)
{
	Player_SkillDamage(Remilia_Skill_A);
	
	switch(Anime_SkillA_FlagA)
	{
		case 1:
			//动作序列
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R1x,Remilia.y-Anime_SkillOffset_R1y,Anime_RemSkillActionPara_1);
			break;
		case 2:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R2x,Remilia.y-Anime_SkillOffset_R2y,Anime_RemSkillActionPara_2);
			break;
		case 3:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R3x,Remilia.y-Anime_SkillOffset_R3y,Anime_RemSkillActionPara_3);
			break;
		case 4:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R4x,Remilia.y-Anime_SkillOffset_R4y,Anime_RemSkillActionPara_4);
			break;
		case 5:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R5x,Remilia.y-Anime_SkillOffset_R5y,Anime_RemSkillActionPara_5);
			break;
		case 6:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R6x,Remilia.y-Anime_SkillOffset_R6y,Anime_RemSkillActionPara_6);
			break;
		case 7:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R7x,Remilia.y-Anime_SkillOffset_R7y,Anime_RemSkillActionPara_7);
			//效果序列 
			Remilia_Skill_A.x = Remilia.x;
			Remilia_Skill_A.y = Remilia.y;
			Remilia_Skill_A.x += Anime_SkillEffect_InitX;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_1);
			Music_RemSkill_A.Play(0);
			break;
		case 8:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R8x,Remilia.y-Anime_SkillOffset_R8y,Anime_RemSkillActionPara_8);
			
			Remilia_Skill_A.x += Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_2);
			break;
		case 9:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R9x,Remilia.y-Anime_SkillOffset_R9y,Anime_RemSkillActionPara_9);
			
			Remilia_Skill_A.x += Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_3);	
			break;
		case 10:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R10x,Remilia.y-Anime_SkillOffset_R10y,Anime_RemSkillActionPara_10);
			
			Remilia_Skill_A.x += Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_4);
			break;
		case 11:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R11x,Remilia.y-Anime_SkillOffset_R11y,Anime_RemSkillActionPara_11);
		
			Remilia_Skill_A.x += Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_5);
			break;
		case 12:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R12x,Remilia.y-Anime_SkillOffset_R12y,Anime_RemSkillActionPara_12);		
			
			Remilia_Skill_A.x += Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_6);
			break;
		case 13:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R13x,Remilia.y-Anime_SkillOffset_R13y,Anime_RemSkillActionPara_13);		
			
			Remilia_Skill_A.x += Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_7);
			break;
		case 14:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R14x,Remilia.y-Anime_SkillOffset_R14y,Anime_RemSkillActionPara_14);			
			
			Remilia_Skill_A.x += Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_8);
			break;
		case 15:
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia.x-Anime_SkillOffset_R15x,Remilia.y-Anime_SkillOffset_R15y,Anime_RemSkillActionPara_15);
			
			Remilia_Skill_A.x += Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AR,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_9);
			//初始化参数 
			Flag_isSkilling = 0;
			Remilia.Flag_Skilling_A = 0;
			Anime_SkillA_FlagA = 1;
			Anime_SkillA_FlagB = 0;
			Remilia_Skill_A.x = -200;
			Remilia_Skill_A.y = -200;
			break;
		default:printf("#1327 Anime_RemiliaSkill_AR ERROR! [%d,%d]\n",Anime_SkillA_FlagA,Anime_SkillA_FlagB);
	}
	
	if(Anime_SkillA_FlagB == Anime_SkillA_Speed)
	{
		Anime_SkillA_FlagB = 0;
		Anime_SkillA_FlagA++;		//换帧 
	}
	Anime_SkillA_FlagB++;

}

/************************************/
/*函数名：Anime_RemiliaSkill_AL	*/
/*功  能：攻击动画	 				*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_RemiliaSkill_AL(void)
{
	Player_SkillDamage(Remilia_Skill_A);

	switch(Anime_SkillA_FlagA)
	{
		case 1:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L1x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L1y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_1);
			break;
		case 2:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L2x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L2y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_2);
			break;
		case 3:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L3x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L3y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_3);
			break;
		case 4:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L4x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L4y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_4);
			break;
		case 5:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L5x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L5y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_5);
			break;
		case 6:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L6x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L6y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_6);
			break;
		case 7:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L7x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L7y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_7);
			//效果序列 
			Remilia_Skill_A.x = Remilia.x;
			Remilia_Skill_A.y = Remilia.y;
			Remilia_Skill_A.x -= Anime_SkillEffect_InitX;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_1);
			Music_RemSkill_A.Play(0);
			break;
		case 8:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L8x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L8y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_8);
			
			Remilia_Skill_A.x -= Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_2);
			break;
		case 9:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L9x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L9y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_9);
			
			Remilia_Skill_A.x -= Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_3);	
			break;
		case 10:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L10x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L10y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_10);
			
			Remilia_Skill_A.x -= Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_4);
			break;
		case 11:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L11x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L11y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_11);
		
			Remilia_Skill_A.x -= Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_5);
			break;
		case 12:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L12x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L12y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_12);		
			
			Remilia_Skill_A.x -= Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_6);
			break;
		case 13:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L13x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L13y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_13);		
			
			Remilia_Skill_A.x -= Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_7);
			break;
		case 14:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L14x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L14y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_14);			
			
			Remilia_Skill_A.x -= Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_8);
			break;
		case 15:
			Anime_Offset_x = Remilia.x-Anime_SkillOffset_L15x;
			Anime_Offset_y = Remilia.y-Anime_SkillOffset_L15y;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Anime_Offset_x,Anime_Offset_y,Anime_RemSkillActionPara_15);
			
			Remilia_Skill_A.x -= Anime_SkillEffect_XGap;
			putimage_withalpha(NULL,IMG_Remilia_Skill_AL,Remilia_Skill_A.x,Remilia_Skill_A.y,Anime_RemSkillEffect_9);
			Flag_isSkilling = 0;
			Remilia.Flag_Skilling_A = 0;
			Anime_SkillA_FlagA = 1;
			Anime_SkillA_FlagB = 0;
			Remilia_Skill_A.x = -200;
			Remilia_Skill_A.y = -200;
			break;
		default:printf("#1463 Anime_RemiliaSkill_AR ERROR! [%d,%d]\n",Anime_SkillA_FlagA,Anime_SkillA_FlagB);
	}
	
	if(Anime_SkillA_FlagB == Anime_SkillA_Speed)
	{
		Anime_SkillA_FlagB = 0;
		Anime_SkillA_FlagA++;		//换帧 
	}
	Anime_SkillA_FlagB++;
}

/************************************/
/*函数名：Anime_RemiliaSkill_A		*/
/*功  能：攻击动画	 				*/
/*参  数：方向  0左  1右			*/
/*返回值： 		 					*/
/************************************/
void Anime_RemiliaSkill_A(bool Direction)
{
	if(Direction && Remilia.Flag_Skilling_A)
		Anime_RemiliaSkill_AR();	
	else if(Remilia.Flag_Skilling_A)
		Anime_RemiliaSkill_AL();
}

/************************************/
/*函数名：Anime_RemNorAtk			*/
/*功  能：攻击动画	 				*/
/*参  数：方向  0左  1右			*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorAtk(bool Direction)
{
	if(Remilia.Flag_NorAtk)
	{
		switch(Remilia.Flag_NorAtk)
		{
			case 1:
				if(Direction)
					Anime_RemNorAtk_AR();
				else
					Anime_RemNorAtk_AL();
				break;
			case 2:
				if(Direction)
					Anime_RemNorAtk_BR();
				else
					Anime_RemNorAtk_BL();
				break;
			case 3:
				if(Direction)
					Anime_RemNorAtk_CR();
				else
					Anime_RemNorAtk_CL();
				break;
		}
	}
}

/************************************/
/*函数名：Anime_RemNorAtk_AR		*/
/*功  能：攻击动画	 				*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorAtk_AR(void)
{
	switch(NorAtk_CtrA)
	{
		case 1:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_AR,Remilia.y - Anime_NorAtkAct_OffY_AR,Anime_RemNorAtk_A_R1);
			Music_NorAtk[0].Play(0);
			break;
		case 2:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_AR,Remilia.y - Anime_NorAtkAct_OffY_AR,Anime_RemNorAtk_A_R2);
			break;
		case 3:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_AR,Remilia.y - Anime_NorAtkAct_OffY_AR,Anime_RemNorAtk_A_R3);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R1);
			break;
		case 4:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_AR,Remilia.y - Anime_NorAtkAct_OffY_AR,Anime_RemNorAtk_A_R4);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R2);
			break;
		case 5:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_AR,Remilia.y - Anime_NorAtkAct_OffY_AR,Anime_RemNorAtk_A_R5);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R3);
			break;
		case 6:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_AR,Remilia.y - Anime_NorAtkAct_OffY_AR,Anime_RemNorAtk_A_R6);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R4);
			Remilia_NorAtk_A.x = Remilia.x;
			Remilia_NorAtk_A.y = Remilia.y - NorAtk_DamOffset_Y;
			NorAtk_CtrA = 1;
			NorAtk_CtrB = 0;
			NorAtk_EftStart = 1;
			Flag_isSkilling = 0;
			Remilia.Flag_NorAtk = 0;
			break;		
	}
	//计数器处理 
	if(NorAtk_CtrB == Anime_NorAtkAct_Speed)
	{
		NorAtk_CtrB = 0;
		NorAtk_CtrA++;
	}
	NorAtk_CtrB++;
}

/************************************/
/*函数名：Anime_RemNorAtk_BR		*/
/*功  能：攻击动画	 				*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorAtk_BR(void)
{
	switch(NorAtk_CtrA)
	{
		case 1:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_AR,Remilia.y - Anime_NorAtkAct_OffY_AR,Anime_RemNorAtk_B_R1);
			Music_NorAtk[1].Play(0);
			break;
		case 2:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_AR,Remilia.y - Anime_NorAtkAct_OffY_AR,Anime_RemNorAtk_B_R2);
			break;
		case 3:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_AR,Remilia.y - Anime_NorAtkAct_OffY_AR,Anime_RemNorAtk_B_R3);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R1);
			break;
		case 4:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_AR,Remilia.y - Anime_NorAtkAct_OffY_AR,Anime_RemNorAtk_B_R4);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R2);
			break;
		case 5:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_AR,Remilia.y - Anime_NorAtkAct_OffY_AR,Anime_RemNorAtk_B_R5);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R3);
			break;
		case 6:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_AR,Remilia.y - Anime_NorAtkAct_OffY_AR,Anime_RemNorAtk_B_R6);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R4);
			Remilia_NorAtk_B.x = Remilia.x;
			Remilia_NorAtk_B.y = Remilia.y - NorAtk_DamOffset_Y;
			NorAtk_CtrA = 1;
			NorAtk_CtrB = 0;
			NorAtk_EftStart = 2;
			Flag_isSkilling = 0;
			Remilia.Flag_NorAtk = 0;
			break;		
	}
	//计数器处理 
	if(NorAtk_CtrB == Anime_NorAtkAct_Speed)
	{
		NorAtk_CtrB = 0;
		NorAtk_CtrA++;
	}
	NorAtk_CtrB++;
}

/************************************/
/*函数名：Anime_RemNorAtk_CR		*/
/*功  能：攻击动画	 				*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorAtk_CR(void)
{
	switch(NorAtk_CtrA)
	{
		case 1:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_CR,Remilia.y - Anime_NorAtkAct_OffY_CR,Anime_RemNorAtk_C_R1);
			Music_NorAtk[2].Play(0);
			break;
		case 2:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_CR,Remilia.y - Anime_NorAtkAct_OffY_CR,Anime_RemNorAtk_C_R2);
			break;
		case 3:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_CR,Remilia.y - Anime_NorAtkAct_OffY_CR,Anime_RemNorAtk_C_R3);
			break;
		case 4:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_CR,Remilia.y - Anime_NorAtkAct_OffY_CR,Anime_RemNorAtk_C_R4);
			break;
		case 5:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_CR,Remilia.y - Anime_NorAtkAct_OffY_CR,Anime_RemNorAtk_C_R5);
			break;
		case 6:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_CR,Remilia.y - Anime_NorAtkAct_OffY_CR,Anime_RemNorAtk_C_R6);
			break;
		case 7:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_CR,Remilia.y - Anime_NorAtkAct_OffY_CR,Anime_RemNorAtk_C_R7);
			break;
		case 8:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_CR,Remilia.y - Anime_NorAtkAct_OffY_CR,Anime_RemNorAtk_C_R8);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R1);
			break;
		case 9:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_CR,Remilia.y - Anime_NorAtkAct_OffY_CR,Anime_RemNorAtk_C_R9);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R2);
			break;
		case 10:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkAct_OffX_CR,Remilia.y - Anime_NorAtkAct_OffY_CR,Anime_RemNorAtk_C_R10);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R3);
			Remilia_NorAtk_C.x = Remilia.x + 32;
			Remilia_NorAtk_C.y = Remilia.y - NorAtkC_DamOffset_Y;
			NorAtk_CtrA = 1;
			NorAtk_CtrB = 0;
			NorAtk_EftStart = 3;
			Flag_isSkilling = 0;
			NorAtk_Type = 1;
			Remilia.Flag_NorAtk = 0;
			break;		
	}
	//计数器处理 
	if(NorAtk_CtrB == Anime_NorAtkAct_Speed)
	{
		NorAtk_CtrB = 0;
		NorAtk_CtrA++;
	}
	NorAtk_CtrB++;
}

/************************************/
/*函数名：Anime_RemNorAtk_AL		*/
/*功  能：攻击动画	 				*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorAtk_AL(void)
{
	switch(NorAtk_CtrA)
	{
		case 1:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_AL,Remilia.y - Anime_NorAtkAct_OffY_AL,Anime_RemNorAtk_A_L1);
			Music_NorAtk[0].Play(0);
			break;
		case 2:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_AL,Remilia.y - Anime_NorAtkAct_OffY_AL,Anime_RemNorAtk_A_L2);
			break;
		case 3:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_AL,Remilia.y - Anime_NorAtkAct_OffY_AL,Anime_RemNorAtk_A_L3);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L1);
			break;
		case 4:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_AL,Remilia.y - Anime_NorAtkAct_OffY_AL,Anime_RemNorAtk_A_L4);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L2);
			break;
		case 5:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_AL,Remilia.y - Anime_NorAtkAct_OffY_AL,Anime_RemNorAtk_A_L5);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L3);
			break;
		case 6:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_AL,Remilia.y - Anime_NorAtkAct_OffY_AL,Anime_RemNorAtk_A_L6);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L4);
			Remilia_NorAtk_A.x = Remilia.x - 32;
			Remilia_NorAtk_A.y = Remilia.y - NorAtk_DamOffset_Y;
			NorAtk_CtrA = 1;
			NorAtk_CtrB = 0;
			NorAtk_EftStart = 1;
			Flag_isSkilling = 0;
			Remilia.Flag_NorAtk = 0;
			break;		
	}
	//计数器处理 
	if(NorAtk_CtrB == Anime_NorAtkAct_Speed)
	{
		NorAtk_CtrB = 0;
		NorAtk_CtrA++;
	}
	NorAtk_CtrB++;
}

/************************************/
/*函数名：Anime_RemNorAtk_BL		*/
/*功  能：攻击动画	 				*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorAtk_BL(void)
{
	switch(NorAtk_CtrA)
	{
		case 1:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_AL,Remilia.y - Anime_NorAtkAct_OffY_AL,Anime_RemNorAtk_B_L1);
			Music_NorAtk[1].Play(0);
			break;
		case 2:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_AL,Remilia.y - Anime_NorAtkAct_OffY_AL,Anime_RemNorAtk_B_L2);
			break;
		case 3:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_AL,Remilia.y - Anime_NorAtkAct_OffY_AL,Anime_RemNorAtk_B_L3);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L1);
			break;
		case 4:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_AL,Remilia.y - Anime_NorAtkAct_OffY_AL,Anime_RemNorAtk_B_L4);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L2);
			break;
		case 5:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_AL,Remilia.y - Anime_NorAtkAct_OffY_AL,Anime_RemNorAtk_B_L5);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L3);
			break;
		case 6:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_AL,Remilia.y - Anime_NorAtkAct_OffY_AL,Anime_RemNorAtk_B_L6);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_R4);
			Remilia_NorAtk_B.x = Remilia.x - 32;
			Remilia_NorAtk_B.y = Remilia.y - NorAtk_DamOffset_Y;
			NorAtk_CtrA = 1;
			NorAtk_CtrB = 0;
			NorAtk_EftStart = 2;
			Flag_isSkilling = 0;
			Remilia.Flag_NorAtk = 0;
			break;		
	}
	//计数器处理 
	if(NorAtk_CtrB == Anime_NorAtkAct_Speed)
	{
		NorAtk_CtrB = 0;
		NorAtk_CtrA++;
	}
	NorAtk_CtrB++;
}

/************************************/
/*函数名：Anime_RemNorAtk_CL		*/
/*功  能：攻击动画	 				*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorAtk_CL(void)
{
	switch(NorAtk_CtrA)
	{
		case 1:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_CL,Remilia.y - Anime_NorAtkAct_OffY_CL,Anime_RemNorAtk_C_L1);
			Music_NorAtk[2].Play(0);
			break;
		case 2:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_CL,Remilia.y - Anime_NorAtkAct_OffY_CL,Anime_RemNorAtk_C_L2);
			break;
		case 3:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_CL,Remilia.y - Anime_NorAtkAct_OffY_CL,Anime_RemNorAtk_C_L3);
			break;
		case 4:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_CL,Remilia.y - Anime_NorAtkAct_OffY_CL,Anime_RemNorAtk_C_L4);
			break;
		case 5:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_CL,Remilia.y - Anime_NorAtkAct_OffY_CL,Anime_RemNorAtk_C_L5);
			break;
		case 6:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_CL,Remilia.y - Anime_NorAtkAct_OffY_CL,Anime_RemNorAtk_C_L6);
			break;
		case 7:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_CL,Remilia.y - Anime_NorAtkAct_OffY_CL,Anime_RemNorAtk_C_L7);
			break;
		case 8:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_CL,Remilia.y - Anime_NorAtkAct_OffY_CL,Anime_RemNorAtk_C_L8);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L1);
			break;
		case 9:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_CL,Remilia.y - Anime_NorAtkAct_OffY_CL,Anime_RemNorAtk_C_L9);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L2);
			break;
		case 10:	
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkAct_OffX_CL,Remilia.y - Anime_NorAtkAct_OffY_CL,Anime_RemNorAtk_C_L10);
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L3);
			Remilia_NorAtk_C.x = Remilia.x - 48;
			Remilia_NorAtk_C.y = Remilia.y - NorAtkC_DamOffset_Y;
			NorAtk_CtrA = 1;
			NorAtk_CtrB = 0;
			NorAtk_EftStart = 3;
			Flag_isSkilling = 0;
			NorAtk_Type = 1;
			Remilia.Flag_NorAtk = 0;
			break;		
	}
	//计数器处理 
	if(NorAtk_CtrB == Anime_NorAtkAct_Speed)
	{
		NorAtk_CtrB = 0;
		NorAtk_CtrA++;
	}
	NorAtk_CtrB++;
}

/************************************/
/*函数名：Anime_RemNorEft			*/
/*功  能：攻击动画	 				*/
/*参  数：方向  0左  1右			*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorEft(bool Direction)
{
	if(NorAtk_EftStart)
	{
		switch(NorAtk_EftStart)
		{
			case 1:
				if(Direction)
					Anime_RemNorEft_AR();
				else
					Anime_RemNorEft_AL();
				break;
			case 2:
				if(Direction)
					Anime_RemNorEft_BR();
				else
					Anime_RemNorEft_BL();
				break;
			case 3:
				if(Direction)
					Anime_RemNorEft_CR();
				else
					Anime_RemNorEft_CL();
				break;
		}
	}
}

/************************************/
/*函数名：Anime_RemNorEft_AR		*/
/*功  能：攻击效果动画	 			*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorEft_AR(void)
{
	Player_SkillDamage(Remilia_NorAtk_A);
		
	switch(NorAtkEft_CtrA)
	{
		case 1:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R5);
			break;
		case 2:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R6);
			break;
		case 3:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R7);
			break;
		case 4:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R8);
			break;
		case 5:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R9);
			break;
		case 6:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R10);
			break;
		case 7:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R11);
			break;
		case 8:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R12);
			break;
		case 9:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R13);
			break;
		case 10:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R14);
			break;
		case 11:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R15);
			break;
		case 12:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R16);
			break;
		case 13:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R17);
			break;
		case 14:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R18);
			break;
		case 15:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R19);
			break;
		case 16:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R20);
			break;
		case 17:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R21);
			break;
		case 18:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R22);
			break;
		case 19:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R23);
			break;
		case 20:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_A_R24);
			NorAtk_EftStart = 0;
			NorAtkEft_CtrA = 1;
			NorAtkEft_CtrB = 0;
			Remilia_NorAtk_A.x = -200;
			Remilia_NorAtk_A.y = -200;
			break;
	}
	//计数器处理 
	if(NorAtkEft_CtrB == Anime_NorAtkEft_Speed)
	{
		NorAtkEft_CtrB = 0;
		NorAtkEft_CtrA++;
	}
	NorAtkEft_CtrB++;
}

/************************************/
/*函数名：Anime_RemNorEft_BR		*/
/*功  能：攻击效果动画	 			*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorEft_BR(void)
{
	Player_SkillDamage(Remilia_NorAtk_B);
		
	switch(NorAtkEft_CtrA)
	{
		case 1:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R5);
			break;
		case 2:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R6);
			break;
		case 3:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R7);
			break;
		case 4:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R8);
			break;
		case 5:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R9);
			break;
		case 6:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R10);
			break;
		case 7:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R11);
			break;
		case 8:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R12);
			break;
		case 9:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R13);
			break;
		case 10:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R14);
			break;
		case 11:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R15);
			break;
		case 12:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R16);
			break;
		case 13:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R17);
			break;
		case 14:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R18);
			break;
		case 15:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R19);
			break;
		case 16:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R20);
			break;
		case 17:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R21);
			break;
		case 18:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R22);
			break;
		case 19:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R23);
			break;
		case 20:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x - Anime_NorAtkEft_OffX_AR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_B_R24);
			NorAtk_EftStart = 0;
			NorAtkEft_CtrA = 1;
			NorAtkEft_CtrB = 0;
			Remilia_NorAtk_B.x = -200;
			Remilia_NorAtk_B.y = -200;
			break;
	}
	//计数器处理 
	if(NorAtkEft_CtrB == Anime_NorAtkEft_Speed)
	{
		NorAtkEft_CtrB = 0;
		NorAtkEft_CtrA++;
	}
	NorAtkEft_CtrB++;
}

/************************************/
/*函数名：Anime_RemNorEft_CR		*/
/*功  能：攻击效果动画	 			*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorEft_CR(void)
{
	Player_SkillDamage(Remilia_NorAtk_C);
		
	switch(NorAtkEft_CtrA)
	{
		case 1:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R4);
			break;
		case 2:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R5);
			break;
		case 3:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R6);
			break;
		case 4:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R7);
			break;
		case 5:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R8);
			break;
		case 6:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R9);
			break;
		case 7:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R10);
			break;
		case 8:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R11);
			break;
		case 9:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R12);
			break;
		case 10:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R13);
			break;
		case 11:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R14);
			break;
		case 12:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R15);
			break;
		case 13:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R16);
			break;
		case 14:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R17);
			break;
		case 15:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R18);
			break;
		case 16:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R19);
			break;
		case 17:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R20);
			break;
		case 18:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R21);
			break;
		case 19:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R22);
			break;
		case 20:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R23);
			break;
		case 21:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_R,Remilia.x + Anime_NorAtkEft_OffX_CR,Remilia.y - Anime_NorAtkEft_OffY_AR,Anime_NorAtkEft_C_R24);
			NorAtk_EftStart = 0;
			NorAtkEft_CtrA = 1;
			NorAtkEft_CtrB = 0;
			Remilia_NorAtk_C.x = -200;
			Remilia_NorAtk_C.y = -200;
			break;
	}
	//计数器处理 
	if(NorAtkEft_CtrB == Anime_NorAtkEft_Speed)
	{
		NorAtkEft_CtrB = 0;
		NorAtkEft_CtrA++;
	}
	NorAtkEft_CtrB++;
}

/************************************/
/*函数名：Anime_RemNorEft_AL		*/
/*功  能：攻击效果动画	 			*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorEft_AL(void)
{
	Player_SkillDamage(Remilia_NorAtk_A);
		
	switch(NorAtkEft_CtrA)
	{
		case 1:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L5);
			break;
		case 2:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L6);
			break;
		case 3:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L7);
			break;
		case 4:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L8);
			break;
		case 5:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L9);
			break;
		case 6:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L10);
			break;
		case 7:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L11);
			break;
		case 8:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L12);
			break;
		case 9:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L13);
			break;
		case 10:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L14);
			break;
		case 11:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L15);
			break;
		case 12:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L16);
			break;
		case 13:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L17);
			break;
		case 14:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L18);
			break;
		case 15:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L19);
			break;
		case 16:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L20);
			break;
		case 17:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L21);
			break;
		case 18:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L22);
			break;
		case 19:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L23);
			break;
		case 20:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_A_L24);
			NorAtk_EftStart = 0;
			NorAtkEft_CtrA = 1;
			NorAtkEft_CtrB = 0;
			Remilia_NorAtk_A.x = -200;
			Remilia_NorAtk_A.y = -200;
			break;
	}
	//计数器处理 
	if(NorAtkEft_CtrB == Anime_NorAtkEft_Speed)
	{
		NorAtkEft_CtrB = 0;
		NorAtkEft_CtrA++;
	}
	NorAtkEft_CtrB++;
}

/************************************/
/*函数名：Anime_RemNorEft_BL		*/
/*功  能：攻击效果动画	 			*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorEft_BL(void)
{
	Player_SkillDamage(Remilia_NorAtk_B);
		
	switch(NorAtkEft_CtrA)
	{
		case 1:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L5);
			break;
		case 2:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L6);
			break;
		case 3:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L7);
			break;
		case 4:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L8);
			break;
		case 5:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L9);
			break;
		case 6:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L10);
			break;
		case 7:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L11);
			break;
		case 8:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L12);
			break;
		case 9:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L13);
			break;
		case 10:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L14);
			break;
		case 11:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L15);
			break;
		case 12:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L16);
			break;
		case 13:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L17);
			break;
		case 14:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L18);
			break;
		case 15:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L19);
			break;
		case 16:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L20);
			break;
		case 17:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L21);
			break;
		case 18:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L22);
			break;
		case 19:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L23);
			break;
		case 20:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_AL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_B_L24);
			NorAtk_EftStart = 0;
			NorAtkEft_CtrA = 1;
			NorAtkEft_CtrB = 0;
			Remilia_NorAtk_B.x = -200;
			Remilia_NorAtk_B.y = -200;
			break;
	}
	//计数器处理 
	if(NorAtkEft_CtrB == Anime_NorAtkEft_Speed)
	{
		NorAtkEft_CtrB = 0;
		NorAtkEft_CtrA++;
	}
	NorAtkEft_CtrB++;
}

/************************************/
/*函数名：Anime_RemNorEft_CL		*/
/*功  能：攻击效果动画	 			*/
/*参  数：							*/
/*返回值： 		 					*/
/************************************/
void Anime_RemNorEft_CL(void)
{
	Player_SkillDamage(Remilia_NorAtk_C);
		
	switch(NorAtkEft_CtrA)
	{
		case 1:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L4);
			break;
		case 2:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L5);
			break;
		case 3:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L6);
			break;
		case 4:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L7);
			break;
		case 5:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L8);
			break;
		case 6:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L9);
			break;
		case 7:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L10);
			break;
		case 8:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L11);
			break;
		case 9:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L12);
			break;
		case 10:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L13);
			break;
		case 11:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L14);
			break;
		case 12:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L15);
			break;
		case 13:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L16);
			break;
		case 14:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L17);
			break;
		case 15:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L18);
			break;
		case 16:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L19);
			break;
		case 17:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L20);
			break;
		case 18:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L21);
			break;
		case 19:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L22);
			break;
		case 20:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L23);
			break;
		case 21:
			putimage_withalpha(NULL,IMG_Rem_NorAtkAct_L,Remilia.x - Anime_NorAtkEft_OffX_CL,Remilia.y - Anime_NorAtkEft_OffY_AL,Anime_NorAtkEft_C_L24);
			NorAtk_EftStart = 0;
			NorAtkEft_CtrA = 1;
			NorAtkEft_CtrB = 0;
			Remilia_NorAtk_C.x = -200;
			Remilia_NorAtk_C.y = -200;
			break;
	}
	//计数器处理 
	if(NorAtkEft_CtrB == Anime_NorAtkEft_Speed)
	{
		NorAtkEft_CtrB = 0;
		NorAtkEft_CtrA++;
	}
	NorAtkEft_CtrB++;
}

/************************************/
/*函数名：Process_reply_props		*/
/*功  能：处理加血道具			 	*/
/*参  数：处理页				  	*/
/*返回值： 		 					*/
/************************************/
void Process_reply_props(int page)
{
	int i;
	char c_temp[10]="+";
	
	setcolor(0x00FF00);
	setfont(40,0,"DFGFuun-W7",0,0,FW_BLACK,0,0,0);
	for(i=0;i<Page_EnemyTypeAmount[page][0];i++)	//单位数量 
	{
		if(MapData_Enemy[page][i].type == 12)
		{
			if(!MapData_Enemy[page][i].Flag_Death )
			{
				putimage_withalpha(NULL,IMG_Reply_Props[MapData_Enemy[page][i].JumpAnime_Ctr],MapData_Enemy[page][i].x,MapData_Enemy[page][i].y - 20);
			
				if(!Props_ReplyHP_Ctr)
				{
					MapData_Enemy[page][i].JumpAnime_Ctr++;
					if(MapData_Enemy[page][i].JumpAnime_Ctr > 11)
					{
						MapData_Enemy[page][i].JumpAnime_Ctr = 0;
					}
				}
			}
			else if(MapData_Enemy[page][i].DeathEffect_Ctr>=0)
			{
				sprintf(String,"%d",MapData_Enemy[page][i].Damage);
				strcat(c_temp,String);
				
				if(MapData_Enemy[page][i].DeathEffect_Ctr > 8)
				{
					putimage_rotate(NULL,IMG_Reply_Eft[8],MapData_Enemy[page][i].x - 34,MapData_Enemy[page][i].y - 25,0.0f,0.0f,0.0f,1,MapData_Enemy[page][i].alpha);
					if(!MapData_Enemy[page][i].Flag_Direction)
						outtextxy(MapData_Enemy[page][i].x - 25,MapData_Enemy[page][i].y - 70 - MapData_Enemy[page][i].DeathEffect_Ctr * 4,c_temp);

					MapData_Enemy[page][i].alpha-=3;
					
					if(MapData_Enemy[page][i].alpha <= 20)
					{
						MapData_Enemy[page][i].DeathEffect_Ctr = -1;
					}
				}
				else
				{
					if(!MapData_Enemy[page][i].Flag_Direction)
						outtextxy(MapData_Enemy[page][i].x - 25,MapData_Enemy[page][i].y - 70 - MapData_Enemy[page][i].DeathEffect_Ctr * 4,c_temp);
					putimage_withalpha(NULL,IMG_Reply_Eft[MapData_Enemy[page][i].DeathEffect_Ctr],MapData_Enemy[page][i].x - 34,MapData_Enemy[page][i].y - 25);
				}
				
				if(!Props_ReplyDeath_Ctr)
				{
					MapData_Enemy[page][i].DeathEffect_Ctr++;
				}
			}
		}
	}
	setcolor(0xFFFFFF);
}

/************************************/
/*函数名：Props_Japariman_HP		*/
/*功  能：回血道具			 		*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Props_Replay_HP(void)
{
	//处理当前页 
	Process_reply_props(Current_Page);
	//处理上一页 
	if(Current_Page!=0)
		Process_reply_props(Current_Page-1);
	//处理下一页 
	if(Current_Page!=Page_Amount-1)
		Process_reply_props(Current_Page+1);
		
	//速度计数器处理 
	if(!Props_ReplyHP_Ctr)
		Props_ReplyHP_Ctr = Props_ReplyHp_AnimeSpeed;
	else if(Props_ReplyHP_Ctr>0)
		Props_ReplyHP_Ctr--;
		
	if(!Props_ReplyDeath_Ctr)
		Props_ReplyDeath_Ctr = Props_ReplyHp_AnimeSpeed;
	else if(Props_ReplyDeath_Ctr > 0)
		Props_ReplyDeath_Ctr--;
}

/************************************/
/*函数名：Process_Cerulean_Blue		*/
/*功  能：蓝色天蓝怪			 	*/
/*参  数：处理页				  	*/
/*返回值： 		 					*/
/************************************/
void Process_Cerulean_Blue(int page)
{
	int i;
	char c_temp[10] = "-";
	
	setfont(40,0,"DFGFuun-W7",0,0,FW_BLACK,0,0,0);
	for(i=0;i<Page_EnemyTypeAmount[page][0];i++)	//单位数量 
	{
		if(MapData_Enemy[page][i].type == Enemy_CeruleanBlue_Number && MapData_Enemy[page][i].Flag_Death == 0)
		{
			if(Enemy_CeruleanBlue_Flag == Enemy_CeruleanBlue_Speed && MapData_Enemy[page][i].Flag_Attack == 0)
			{
				if(Check_RightBlock(i,page))		//若右侧有方块
					 MapData_Enemy[page][i].Flag_Direction = 0;//左移标志 
				else if(Check_LeftBlock(i,page))	//若左侧有方块
					 MapData_Enemy[page][i].Flag_Direction = 1;//右移标志
					 
				if(!Check_BelowBlock(i,page))	//若脚下无方块 
					MapData_Enemy[page][i].Flag_Direction = !MapData_Enemy[page][i].Flag_Direction;//向相反方向移动 

				if(MapData_Enemy[page][i].Flag_Direction)	//若右移
					MapData_Enemy[page][i].x++;	 
				else										//若左移			
					MapData_Enemy[page][i].x--;					
			}
			
			if(MapData_Enemy[page][i].Flag_Direction)
				putimage_withalpha(NULL,IMG_Enemy_Cerulean_Blue_R[Anime_CeruBlue_CtrA],MapData_Enemy[page][i].x - Anime_CeruleanBlueOffset_X,MapData_Enemy[page][i].y - Anime_CeruleanBlueOffset_Y);
			else
				putimage_withalpha(NULL,IMG_Enemy_Cerulean_Blue_L[Anime_CeruBlue_CtrA],MapData_Enemy[page][i].x - Anime_CeruleanBlueOffset_X,MapData_Enemy[page][i].y - Anime_CeruleanBlueOffset_Y);
			
			#ifdef	ENABLE_Aux_Frame
			Frame_Enemy(MapData_Enemy[page][i]);
			#endif
		}
		//死亡处理 
		else if(MapData_Enemy[page][i].Flag_Death && MapData_Enemy[page][i].DeathEffect_Ctr>=0 && MapData_Enemy[page][i].type == Enemy_CeruleanBlue_Number)
		{
			putimage_withalpha(NULL,IMG_Enemy_CerBlue_Death[MapData_Enemy[page][i].DeathEffect_Ctr],MapData_Enemy[page][i].x-Anime_CerBlue_DeathOffX,MapData_Enemy[page][i].y-Anime_CerBlue_DeathOffY);
			
			if(Anime_CerBlue_DeathFlag == Enemy_CeruleanBlue_DeathSpeed)
			{
				MapData_Enemy[page][i].DeathEffect_Ctr++;
				
				if(MapData_Enemy[page][i].DeathEffect_Ctr == 16)
					MapData_Enemy[page][i].DeathEffect_Ctr = -1;
			}
		}
		//攻击处理 
		if(MapData_Enemy[page][i].AnimeAttack_Ctr>=0)
		{
			sprintf(String,"%d",MapData_Enemy[page][i].Damage);
			strcat(c_temp,String);
			
			setcolor(0xFFFF00);
			outtextxy(Remilia.x - 20,Remilia.y - MapData_Enemy[page][i].AnimeAttack_Ctr * 4,c_temp);
			
			if(MapData_Enemy[page][i].Flag_Direction)
			putimage_withalpha(NULL,IMG_Enemy_Attack_Normal_L[MapData_Enemy[Current_Page][i].AnimeAttack_Ctr],Remilia.x-Anime_CerBlue_AttOffsetX_L,Remilia.y-Anime_CerBlue_AttOffsetY);
			else
			putimage_withalpha(NULL,IMG_Enemy_Attack_Normal_R[MapData_Enemy[Current_Page][i].AnimeAttack_Ctr],Remilia.x+Anime_CerBlue_AttOffsetX_R,Remilia.y-Anime_CerBlue_AttOffsetY);

			if(Enemy_CerBlue_AttCtr == Anime_CeruBlue_AttSpeed)
			{
				MapData_Enemy[page][i].AnimeAttack_Ctr++;
				
				if(MapData_Enemy[page][i].AnimeAttack_Ctr == 8)
					MapData_Enemy[page][i].AnimeAttack_Ctr = -1;
			}
		}
	}
}

/************************************/
/*函数名：Process_Cerulean_Blue		*/
/*功  能：粉色天蓝怪			 	*/
/*参  数：处理页				  	*/
/*返回值： 		 					*/
/************************************/
void Process_Cerulean_Pink(int page)
{
	int i,j;
	char c_temp[10] = "-";
	
	setfont(40,0,"DFGFuun-W7",0,0,FW_BLACK,0,0,0);
	for(i=0;i<Page_EnemyTypeAmount[page][0];i++)	//单位数量 
	{
		if(MapData_Enemy[page][i].type == Enemy_CeruleanPink_Number && MapData_Enemy[page][i].Flag_Death == 0)
		{
			if(!Anime_CeruPink_CtrB)//速度控制 
			{
				//移动处理 
				if(MapData_Enemy[page][i].JumpHeight_Ctr < Enemy_CeruleanPink_JumpHeight)
				{
					j = Math_Acceleration((Enemy_CeruleanPink_JumpHeight - MapData_Enemy[page][i].JumpHeight_Ctr));
					MapData_Enemy[page][i].y -= j; //上移 
					MapData_Enemy[page][i].Flag_Direction = 1;
					MapData_Enemy[page][i].JumpHeight_Ctr += j;
					MapData_Enemy[page][i].FallHeight_Ctr = 0;
				}
				else
				{	
					if(MapData_Enemy[page][i].y < MapData_Enemy[page][i].JumpStart_Loc)
					{
						j = Math_Acceleration(MapData_Enemy[page][i].FallHeight_Ctr);
						MapData_Enemy[page][i].y += j; //下移
						MapData_Enemy[page][i].Flag_Direction = 0;
						MapData_Enemy[page][i].FallHeight_Ctr += j;
					}
					else
					{
						MapData_Enemy[page][i].JumpHeight_Ctr = 0;
						Music_PinkJump.Play(0);
					}
				}
				
				if(MapData_Enemy[page][i].Flag_Direction)//上移 
				{
					//根据高度换算图像序号 
					j = Enemy_CeruleanPink_JumpHeight / 7;
					MapData_Enemy[page][i].JumpAnime_Ctr = MapData_Enemy[page][i].JumpHeight_Ctr / j;
					
					if(MapData_Enemy[page][i].JumpAnime_Ctr > 6)
					{
						MapData_Enemy[page][i].JumpAnime_Ctr = 6;
					}
				}
				else	//下移
				{
					j = Enemy_CeruleanPink_JumpHeight / 7;
					MapData_Enemy[page][i].JumpAnime_Ctr = MapData_Enemy[page][i].FallHeight_Ctr / j + 7;

					if(MapData_Enemy[page][i].JumpAnime_Ctr > 13)
					{
						MapData_Enemy[page][i].JumpAnime_Ctr = 13;
					}
				}
			}
			putimage_withalpha(NULL,IMG_Enemy_Cerulean_Pink[MapData_Enemy[page][i].JumpAnime_Ctr],MapData_Enemy[page][i].x-10,MapData_Enemy[page][i].y-10);
			
			#ifdef	ENABLE_Aux_Frame
			Frame_Enemy(MapData_Enemy[page][i]);
			#endif
		}
		//死亡处理 
		else if(MapData_Enemy[page][i].Flag_Death && MapData_Enemy[page][i].DeathEffect_Ctr>=0 && MapData_Enemy[page][i].type == Enemy_CeruleanPink_Number)
		{
			putimage_withalpha(NULL,IMG_Enemy_CerPink_Death[MapData_Enemy[page][i].DeathEffect_Ctr],MapData_Enemy[page][i].x-Anime_CerBlue_DeathOffX,MapData_Enemy[page][i].y-Anime_CerBlue_DeathOffY);
			
			if(Anime_CerBlue_DeathFlag == Enemy_CeruleanBlue_DeathSpeed)
			{
				MapData_Enemy[page][i].DeathEffect_Ctr++;
				
				if(MapData_Enemy[page][i].DeathEffect_Ctr == 16)
					MapData_Enemy[page][i].DeathEffect_Ctr = -1;
			}
		}
		//攻击处理 
		if(MapData_Enemy[page][i].AnimeAttack_Ctr>=0)
		{
			sprintf(String,"%d",MapData_Enemy[page][i].Damage);
			strcat(c_temp,String);
			
			setcolor(0xFFFF00);
			outtextxy(Remilia.x - 20,Remilia.y - MapData_Enemy[page][i].AnimeAttack_Ctr * 4,c_temp);
			
			if(MapData_Enemy[page][i].Flag_Direction)
			putimage_withalpha(NULL,IMG_Enemy_Attack_Normal_L[MapData_Enemy[Current_Page][i].AnimeAttack_Ctr],Remilia.x-Anime_CerBlue_AttOffsetX_L,Remilia.y-Anime_CerBlue_AttOffsetY);
			else
			putimage_withalpha(NULL,IMG_Enemy_Attack_Normal_R[MapData_Enemy[Current_Page][i].AnimeAttack_Ctr],Remilia.x+Anime_CerBlue_AttOffsetX_R,Remilia.y-Anime_CerBlue_AttOffsetY);

			if(Enemy_CerBlue_AttCtr == Anime_CeruBlue_AttSpeed)
			{
				MapData_Enemy[page][i].AnimeAttack_Ctr++;
				
				if(MapData_Enemy[page][i].AnimeAttack_Ctr == 8)
					MapData_Enemy[page][i].AnimeAttack_Ctr = -1;
			}
		}
	}
}

/************************************/
/*函数名：Enemy_Cerulean_Pink		*/
/*功  能：敌人-天蓝怪-粉	 		*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/*描  述：只能纵向移动，无远程攻击	*/ 
/************************************/
void Enemy_Cerulean_Pink(void)
{
	//处理当前页 
	Process_Cerulean_Pink(Current_Page);
	//处理上一页 
	if(Current_Page!=0)
		Process_Cerulean_Pink(Current_Page-1);
	//处理下一页 
	if(Current_Page!=Page_Amount-1)
		Process_Cerulean_Pink(Current_Page+1);
		
	//速度计数器处理 
	if(!Anime_CeruPink_CtrB)
		Anime_CeruPink_CtrB = Enemy_CeruleanPink_Speed;
	else if(Anime_CeruPink_CtrB>0)
		Anime_CeruPink_CtrB--;
}

/************************************/
/*函数名：Enemy_Cerulean_Blue		*/
/*功  能：敌人-天蓝怪-蓝	 		*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/*描  述：只能横向移动，无远程攻击	*/ 
/************************************/
void Enemy_Cerulean_Blue(void)
{
	int i,j;
	
	if(Anime_CeruBlue_CtrA > 13)
		Anime_CeruBlue_CtrA = 0;
	
	//处理当前页 
	Process_Cerulean_Blue(Current_Page);
	//处理上一页 
	if(Current_Page!=0)
		Process_Cerulean_Blue(Current_Page-1);
	//处理下一页 
	if(Current_Page!=Page_Amount-1)
		Process_Cerulean_Blue(Current_Page+1);
	
	
	//移动动画速度计数器处理 
	if(Anime_CeruBlue_CtrB == Anime_CeruleanBlue_Speed)
	{
		Anime_CeruBlue_CtrB = 0;
		Anime_CeruBlue_CtrA++;		//换帧 
	}
	Anime_CeruBlue_CtrB++;
	//移动速度计数器处理 
	if(Enemy_CeruleanBlue_Flag == Enemy_CeruleanBlue_Speed)
	{
		Enemy_CeruleanBlue_Flag = 0;
	}
	Enemy_CeruleanBlue_Flag++;
	//死亡动画速度计数器处理 
	if(Anime_CerBlue_DeathFlag == Enemy_CeruleanBlue_DeathSpeed)
	{
		Anime_CerBlue_DeathFlag = 0;
	}
	Anime_CerBlue_DeathFlag++;
	//攻击动画计数器处理 
	if(Enemy_CerBlue_AttCtr == Anime_CeruBlue_AttSpeed)
	{
		Enemy_CerBlue_AttCtr = 0;
	}
	Enemy_CerBlue_AttCtr++;
}

/************************************/
/*函数名：Enemy_Damage_Normal		*/
/*功  能：敌对伤害			 		*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Enemy_Damage_Normal(void)
{
	int i;
	
	if(!Remilia.Flag_Barrage)
	for(i=0;i<Page_EnemyTypeAmount[Current_Page][0];i++)
	{
		if(!MapData_Enemy[Current_Page][i].Flag_Death)
			if(MapData_Enemy[Current_Page][i].x+MapData_Enemy[Current_Page][i].Length>Remilia.x)
				if(MapData_Enemy[Current_Page][i].x<Remilia.x+Remilia.Length)
					if(MapData_Enemy[Current_Page][i].y+MapData_Enemy[Current_Page][i].Width>Remilia.y)
						if(MapData_Enemy[Current_Page][i].y<Remilia.y+Remilia.Width)
						{
							Check_EnemyDamageNormal = 1;
							
							MapData_Enemy[Current_Page][i].Flag_Attack = 1;
							
							if(!MapData_Enemy[Current_Page][i].Attack_Ctr && MapData_Enemy[Current_Page][i].type != 12)
							{
								if(MapData_Enemy[Current_Page][i].type == 11)
									MapData_Enemy[Current_Page][i].Damage  = random(100)-50+Enemy_CeruleanPink_Damage - Remilia.Defense;
								if(MapData_Enemy[Current_Page][i].type == 10)
									MapData_Enemy[Current_Page][i].Damage  = random(100)-50+Enemy_CeruleanBlue_Damage - Remilia.Defense;
								
								if(MapData_Enemy[Current_Page][i].Damage < 0)
									MapData_Enemy[Current_Page][i].Damage = 0;
									
								Remilia.HP -= MapData_Enemy[Current_Page][i].Damage;
								Remilia.Flag_Beaten = 1;
								Remilia.Flag_Direction = !MapData_Enemy[Current_Page][i].Flag_Direction;
								
								MapData_Enemy[Current_Page][i].Attack_Ctr = Enemy_CeruBlue_AttTimGap;
								
								if(Remilia.HP<=0)
									Remilia.Flag_Death = 1;
									
								if(MapData_Enemy[Current_Page][i].AnimeAttack_Ctr < 0)
								{
									Music_CerBlueAttN.Play(0);
									MapData_Enemy[Current_Page][i].AnimeAttack_Ctr = 0;
								}
							}
							
							if(MapData_Enemy[Current_Page][i].type == 12)
							{
								if(Music_HPreply.GetPlayStatus() == MUSIC_MODE_STOP)
									Music_HPreply.Play(0);
								
								Remilia.HP += MapData_Enemy[Current_Page][i].Damage;
								if(Remilia.HP > Remilia_HP)
									Remilia.HP = Remilia_HP;
									
								MapData_Enemy[Current_Page][i].Flag_Death = 1;
								MapData_Enemy[Current_Page][i].DeathEffect_Ctr = 0;
							}
						}
		if(!Check_EnemyDamageNormal)
		{
			MapData_Enemy[Current_Page][i].Flag_Attack = 0;
		}
		Check_EnemyDamageNormal = 0;
		if(MapData_Enemy[Current_Page][i].Attack_Ctr > 0)
		{
			MapData_Enemy[Current_Page][i].Attack_Ctr--;
		}
	}
}

/************************************/
/*函数名：Process_PlayerMoveRight 	*/
/*功  能：处理右移动 		 		*/
/*参  数：			 		 		*/
/*返回值： 		 					*/
/************************************/
void Process_PlayerMoveRight(void)
{
	if(keystate(Keyboard_MoveRight))
	{
		if(!Check_RightBlock(-1,Current_Page))//判断右侧是否无方块
		{	
			Remilia.Flag_Direction=1;
			Flag_isMoving = 1;
			
			if(!isBossStage)
			{
				Remilia.x++;
				Graphics_R_Shift();
			}
			else
			{
				if(Remilia.x < 980)
				Remilia.x++;
			}
		}
	}
}

/************************************/
/*函数名：Process_PlayerMoveLeft	*/
/*功  能：处理左移动 		 		*/
/*参  数：			 		 		*/
/*返回值： 		 					*/
/************************************/
void Process_PlayerMoveLeft(void)
{
	if(keystate(Keyboard_MoveLeft)){
		if(!Check_LeftBlock(-1,Current_Page)){//判断X负半轴是否有碰撞，Y轴是否可通过
			Remilia.Flag_Direction=0;
			Flag_isMoving = 1;
			
			if(!isBossStage)
			{
				Remilia.x--;
				Graphics_L_Shift();
			}
			else
			{
				if(Remilia.x > 0)
					Remilia.x--;
			}
		}
	}
}

/************************************/
/*函数名：Process_PlayerStartJump	*/
/*功  能：处理跳跃起始	 			*/
/*参  数：			 		 		*/
/*返回值： 		 					*/
/************************************/
void Process_PlayerStartJump(void)
{
	if(keystate(Keyboard_Jump)&&!JumpDelay)
	{
		if(Check_BelowBlock(-1,Current_Page)&&!Check_TopBlock(-1,Current_Page)&&!Remilia.Flag_Jump)
		{//下方有方块&&上方无方块&&非向上跳跃状态 
			Move_Jump_StartHeight = Remilia.y;		//记录起点高度 
			Move_Jumped_Height = 0;	//已跳跃高度清零 
			Remilia.Flag_Jump = 1;	//置向上跳跃标志位 
			JumpDelay = Remilia_JumpDelay;//跳跃延时 
		}
	}
}

/************************************/
/*函数名：Process_PlayerJumpingUp	*/
/*功  能：处理跳跃上升		 		*/
/*参  数：			 		 		*/
/*返回值： 		 					*/
/************************************/
void Process_PlayerJumpingUp(void)
{	
	Process_PlayerStartJump();
	
	if(Remilia.Flag_Jump&&!Check_TopBlock(-1,Current_Page)&&Move_Jumped_Height<Remilia_JumpHeight)
	{//向上跳跃标志&&头顶无方块&&未达到设定跳跃高度 
		Remilia.y--;
		//Flag_isMoving = 0;
		Move_Jumped_Height++;
		#ifdef ENABLE_Monitor
		printf("#947 Remilia Location[X:%d,Y:%d][Page:%d]",Remilia.x,Remilia.y,Current_Page);
		printf("%d %d\n",Page_BorderLine[0],Page_BorderLine[1]);
		#endif
	}
	else if(Remilia.Flag_Jump)
	{
		Remilia.Flag_Jump = 0;//若不满足条件则清跳跃标志位，进行下落 
	}	
}

/************************************/
/*函数名：Process_PlayerDropDown	*/
/*功  能：处理下落			 		*/
/*参  数：			 		 		*/
/*返回值： 		 					*/
/************************************/
void Process_PlayerDropDown(void)
{
	if(!Remilia.Flag_Jump&&!Check_BelowBlock(-1,Current_Page))
	{//不在跳跃中且脚下无方块则下落
		Remilia.y++;
		#ifdef ENABLE_Monitor
		printf("#970 Remilia Location[X:%d,Y:%d][Page:%d]",Remilia.x,Remilia.y,Current_Page);
		printf("%d %d\n",Page_BorderLine[0],Page_BorderLine[1]);
		#endif
		//Flag_isMoving = 0;
	}
	else if(Check_BelowBlock(-1,Current_Page))
	{
		Remilia.Flag_Jump = 0;//若脚下有方块则清跳跃标志位
		if(JumpDelay>0)
			JumpDelay--;
	}
	
}

/************************************/
/*函数名：Process_PlayerDefense 	*/
/*功  能：防御				 		*/
/*参  数：					 		*/
/*返回值： 		 					*/
/************************************/
void Process_PlayerDefense(void)
{
	if(keystate(Keyboard_Defense))
	{
		if(Check_BelowBlock(-1,Current_Page))
			Remilia.Defense = Remilia_Defense;
	}
	else
	{
		Remilia.Defense = 0;
	}
}

/************************************/
/*函数名：Process_PlayerSkill 		*/
/*功  能：技能释放			 		*/
/*参  数：					 		*/
/*返回值： 		 					*/
/************************************/
void Process_PlayerSkill(void)
{
	if(Remilia.MP >= SkillA_MP)
		if(keystate(Keyboard_SkillA)&& !Flag_isSkilling && !SkillA_CDcounter)
		{
			SkillA_CDcounter = SkillA_CD;
			Remilia.MP -= SkillA_MP;
			Flag_isSkilling = 1;
			Remilia.Flag_Skilling_A = 1;
		}
		
	if(Remilia.MP >= SkillB_MP)
		if(keystate(Keyboard_SkillB) && !Flag_SkillArrow_B && !Flag_isSkilling && !SkillB_CDcounter)
		{
			SkillB_CDcounter = SkillB_CD;
			Remilia.MP -= SkillB_MP;
			Flag_isSkilling = 1;
			Remilia.Flag_Skilling_B = 1;
		}
		
	if(Remilia.MP >= SkillB_MP)
		if(keystate(Keyboard_Barrage) && !Flag_isSkilling && !Barrage_CDcounter)
		{
			Barrage_CDcounter = SkillBarrage_CD;
			Remilia.MP -= SkillBarrage_MP;
			Flag_isSkilling = 1;
			Remilia.Flag_Barrage = 1;
		}
		
	if(keystate(Keyboard_NorAtk) && !Remilia.Flag_NorAtk && !Flag_isSkilling && !NorAtk_CDcounter)
	{	
		Flag_isSkilling = 1;
		NorAtk_CDcounter = NorAtk_CD;
		Remilia.Flag_NorAtk = NorAtk_Type;
		
		if(NorAtk_TypeCtr && NorAtk_Type < 3)
		{
			NorAtk_Type++;
		}
		NorAtk_TypeCtr = NorAtk_TypeTimGap;
	}

	if(NorAtk_TypeCtr>0)
		NorAtk_TypeCtr--;
	else
		NorAtk_Type = 1;
}

/************************************/
/*函数名：Check_MouseLocation		*/
/*功  能：确定鼠标是否在区域	 	*/
/*参  数：区域						*/
/*返回值：1在当前区域 0不在当前区域	*/
/************************************/
bool Check_MouseLocation(int x1,int y1,int x2,int y2)
{
	if(Mouse.x>=x1)
		if(Mouse.x<=x2)
			if(Mouse.y>=y1)
				if(Mouse.y<=y2)
					return(1);
	return(0);
}

/************************************/
/*函数名： GUI_GameOver				*/
/*功  能： GUI处理函数		 		*/
/*参  数： 		 					*/
/*返回值： 		 					*/
/************************************/
void GUI_GameOver(void)
{
	//初始化界面 
	putimage(0,150,IMG_Gameover);
	getimage_pngfile(IMG_ButtonUnselected,"ScenesImage\\Menu\\Button_Overback1.png");
	putimage(479,192+150,IMG_ButtonUnselected);
	getimage_pngfile(IMG_Buttonselected,"ScenesImage\\Menu\\Button_Overback2.png");
	
	Sleep(200);
	
	//鼠标处理
	while(is_run())
	{
		SYS_GetMouse();
		
		if(keystate(VK_ESCAPE))
			exit(0);//退出游戏 
		
		if(Check_MouseLocation(AREA_GameOver))
		{
			if(Music_GUISelected_1.GetPlayStatus() == MUSIC_MODE_STOP && Flag_GUIMusStu == 0)
			{
				Flag_GUIMusStu = 1;
				Music_GUISelected_1.Play(0);
			}			
				
			putimage(479,192+150,IMG_Buttonselected);
			
			if(Mouse.is_left)
			{
				if(Music_GUIConfirm_1.GetPlayStatus() == MUSIC_MODE_STOP)
				Music_GUIConfirm_1.Play(0);
				break;
			}	
		}
		else
		{
			Flag_GUIMusStu = 0;
			putimage(479,192+150,IMG_ButtonUnselected);
		}
		
		Sleep(1);	
	}	
	
	SYS_Parameter_Init();
	GUI_GameStart();
}

/************************************/
/*函数名： GUI_GameVictory			*/
/*功  能： GUI处理函数		 		*/
/*参  数： 		 					*/
/*返回值： 		 					*/
/************************************/
void GUI_GameVictory(void)
{
	Music_BossBGM.Stop();
	
	getimage_pngfile(IMG_PublicImage,"ScenesImage\\Menu\\victory.png");
	getimage_pngfile(IMG_ButtonUnselected,"ScenesImage\\Menu\\next2.png");
	getimage_pngfile(IMG_Buttonselected,"ScenesImage\\Menu\\next1.png");
	
	Music_GameVictory.Play(0);

	while(is_run())
	{
		putimage(0,0,IMG_PublicImage);
		putimage_withalpha(NULL,IMG_ButtonUnselected,800,569);
		
		SYS_GetMouse();
		
		if(keystate(VK_ESCAPE))
			exit(0);//退出游戏 
		
		if(Check_MouseLocation(AREA_Victory))
		{
			if(Music_GUISelected_1.GetPlayStatus() == MUSIC_MODE_STOP && Flag_GUIMusStu == 0)
			{
				Flag_GUIMusStu = 1;
				Music_GUISelected_1.Play(0);
			}
				
			putimage_withalpha(NULL,IMG_Buttonselected,800,569);
			
			if(Mouse.is_left)
			{
				if(Music_GUIConfirm_1.GetPlayStatus() == MUSIC_MODE_STOP)
				Music_GUIConfirm_1.Play(0);
				break;
			}	
		}
		else
		{
			Flag_GUIMusStu = 0;
			putimage_withalpha(NULL,IMG_ButtonUnselected,800,569);
		}
		
		delay_fps(60);
		cleardevice();
	}
	
	SYS_Parameter_Init();
	GUI_GameStart();
}

/************************************/
/*函数名： GUI_GameStart			*/
/*功  能： GUI处理函数		 		*/
/*参  数： 		 					*/
/*返回值： 		 					*/
/************************************/
void GUI_GameStart(void)
{
	int i,r=255,g=255,b=255;
	bool flag=0;
	//初始化界面 
	getimage_pngfile(IMG_PublicImage,"ScenesImage\\Menu\\Start\\StartBK.png");
	putimage(0,0,IMG_PublicImage);
	getimage_pngfile(IMG_ButtonUnselected,"ScenesImage\\Menu\\Start\\StartButton1.png");
	putimage_withalpha(NULL,IMG_ButtonUnselected,334,470);
	getimage_pngfile(IMG_Buttonselected,"ScenesImage\\Menu\\Start\\StartButton2.png");
	Music_StartBGM.Play(0);
	
	Sleep(200);
	
	//鼠标处理
	while(is_run())
	{
		SYS_GetMouse();
		
		if(keystate(VK_ESCAPE))
			exit(0);//退出游戏 
		
		if(Check_MouseLocation(AREA_Start_1))
		{
			
			if(Music_GUISelected_1.GetPlayStatus() == MUSIC_MODE_STOP && Flag_GUIMusStu == 0)
			{
				Flag_GUIMusStu = 1;
				Music_GUISelected_1.Play(0);
			}			
			
			if(!Flag_GUIPicStu)
			{
				putimage_withalpha(NULL,IMG_Buttonselected,334,470);
				Flag_GUIPicStu = 1;
			}
			
			if(Mouse.is_left)
			{
				if(Music_GUIConfirm_1.GetPlayStatus() == MUSIC_MODE_STOP)
				Music_GUIConfirm_1.Play(0);
				break;
			}	
		}
		else
		{
			Flag_GUIMusStu = 0;
			if(Flag_GUIPicStu)
			{
				putimage_withalpha(NULL,IMG_ButtonUnselected,334,470);
				Flag_GUIPicStu = 0;
			}
		}
		
		Sleep(1);
	}

	setfont(20,0,"DFGFuun-W7",0,0,FW_MEDIUM,0,0,0);
	getimage(IMG_PublicImage,"ScenesImage\\Menu\\Start\\Description.png");
	for(i=0;i<400;i++)
	{
		setcolor(EGERGB(r,g,b));
		putimage(0,0,IMG_PublicImage);
		outtextxy(720,620,"PRESS SPACE TO SKIP >>");
		
		if(r <= 128)
			flag = 1;
		if(r >= 255)
			flag = 0;
		
		if(flag)
		{
			r+=3;
			g+=3;
			b+=3;
		}
		else
		{
			r-=3;
			g-=3;
			b-=3;
		}
		
		delay_fps(60);
		cleardevice();
		
		if(keystate(VK_SPACE))
			break;
	}
	
	putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	Music_StartBGM.Stop();
	Music_BattleBGM.Play(0);
	
	for(i=0;i<10;i++)
	{
		putimage_withalpha(NULL,IMG_Remilia_Start[i],Remilia_initX-96,Remilia_initY-96);
		delay_fps(10);
		putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	}
	for(i=10;i<19;i++)
	{
		putimage_withalpha(NULL,IMG_Remilia_Start[9],Remilia_initX-96,Remilia_initY-96);
		putimage_withalpha(NULL,IMG_Remilia_Start[i],Remilia_initX-32,Remilia_initY-32);
		delay_fps(10);
		putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	}
	putimage_withalpha(NULL,IMG_Remilia_Start[18],Remilia_initX-32,Remilia_initY-32);
	delay_fps(1);
}

/************************************/
/*函数名： GUI_HpMp_bar				*/
/*功  能： 绘制血槽			 		*/
/*参  数： 		 					*/
/*返回值： 		 					*/
/************************************/
void GUI_HpMp_bar(void) 
{
	float HP,MP,CDA=0,CDB=0,CDC=0;
	setcolor(WHITE);
	setfont(15,0,"DFGFuun-W7",0,0,FW_MEDIUM,0,0,0);
	
	if(Remilia.HP <= 0)
		Remilia.HP = 0;
	if(Remilia.MP <= 0)
		Remilia.MP = 0;
	
	//百分比换算 
	HP = Remilia.HP / (Remilia_HP*1.0f) * 370;
	MP = Remilia.MP / (Remilia_MP*1.0f) * 370;
	//绘制血槽 
	setfillcolor(0xC00000);
	if(Remilia.HP > 0)
		bar(120,21,(int)HP+120,36);
	setfillcolor(0x4472C4);
	if(Remilia.MP > 0)
		bar(120,45,(int)MP+120,60);
	//显示数字 
	sprintf(String,"%.0f",Remilia.HP);
	strcat(String,Str_RemiliaHP);
	outtextxy(257,21,String);
	
	sprintf(String,"%d",Remilia.MP);
	strcat(String,Str_RemiliaMP);
	outtextxy(257,45,String);

	outtextxy(10,80,"ShockWave :");
	if(SkillA_CDcounter > 0)
	{
		CDA = SkillA_CDcounter / (SkillA_CD * 1.0f) * 100;
		sprintf(String,"%d",(int)CDA);
		outtextxy(110,80,String);
	}
	else
		outtextxy(110,80,"Ready!");
	
	outtextxy(10,100,"RedArrow  :");
	if(SkillB_CDcounter > 0)
	{
		CDB = SkillB_CDcounter / (SkillB_CD * 1.0f) * 100;
		sprintf(String,"%d",(int)CDB);
		outtextxy(110,100,String);
	}
	else
		outtextxy(110,100,"Ready!");
	
	outtextxy(10,120,"Barrage     :");
	if(Barrage_CDcounter > 0)
	{
		CDC = Barrage_CDcounter / (SkillBarrage_CD * 1.0f) * 100;
		sprintf(String,"%d",(int)CDC);
		outtextxy(110,120,String);
	}
	else
		outtextxy(110,120,"Ready!");
	
	//显示框架 
	putimage_withalpha(NULL,IMG_HPMPBar,10,10);
	
	//绘制BOSS血条 
	if(isBossStage)
	{
		HP = Boss.HP/(Enemy_BoosHP*1.0)*370;
		setfillcolor(0xC00000);
		if(HP > 0)
		{
			bar(532,21,(int)HP+532,36);
		}
		else
		{
			Boss.HP = 0;
		}
		
		sprintf(String,"%d",Boss.HP);
		strcat(String,Str_BossHP);
		outtextxy(700,20,String);

		if(Boss.AtkCD_Ctr < 250)
		{
			putimage_withalpha(NULL,IMG_BossHPMPBar_1,520,10);
		}
		else
		{
			putimage_withalpha(NULL,IMG_BossHPMPBar_2,520,10);
		}

	}
}

/************************************/
/*函数名：BossStage					*/
/*功  能：BOSS关卡			 		*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
bool BossStage(void)
{
	int i;
	Remilia.x = Remilia_initX;
	CurrentScreen_Xaxis = Window_TotalLength-WindowSize_L;
	putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	
	//初始化BOSS 
	Boss.HP = Enemy_BoosHP;
	Boss.Flag_Death = 0;
	Boss.Length = 179;
	Boss.Width = 182;
	Boss.x = 750;
	Boss.y = 200;
	Boss.Direction = -1;
	Boss.DeathEffect_Ctr = -1;
	Boss.Flag_HitEffect = 0;
	Boss.HitEffect_Ctr = 0;
	Boss.MoveSpeed_Ctr = 0;
	Boss.BarrageType = 4;
	Boss.Target_Y = Anime_BossMove_OffsetY;
	Boss.isSilling = 0;
	Boss.AtkCD_Ctr = Enemy_BossAtk_CD;
	Boss.DeathEffect_Ctr = 0;
	Boss.DeathEftSpeed_Ctr = 0;
	Remilia.BeatenBossTentacle_Ctr = -1;
	
	for(i=0;i<BossAtk_Tentacle_Amount;i++)
	{
		randomize();
		BossTentacle[i].x = WindowSize_L + random(300);
		BossTentacle[i].y = random(WindowSize_H - 200);
	}
	
	setcolor(WHITE);
	
	Music_BattleBGM.Stop();	
	Music_BossBGM.Play(0);
	
	while(is_run())
	{
		if(keystate(VK_ESCAPE))
		exit(0);//退出游戏 
		
		if(Music_BossBGM.GetPlayStatus() == MUSIC_MODE_STOP)
			Music_BossBGM.Play(0);
			
		if(Remilia.y>=WindowSize_H || Remilia.HP<=0)
		{
			SYS_Game_Over();
			return(0);
		}
		
		randomize();//随机数重置 
		
		if(Boss.AtkCD_Ctr < 0)
			Boss.AtkCD_Ctr = Enemy_BossAtk_CD;
		
		if(!Boss.isSilling)
		{
			Boss.SkillSelect = random(5)+1;//随机技能 
			if(Boss.SkillSelect > 3)
			{
				Boss.SkillSelect = 1;//提高弹幕技能的概率 
			}
			Boss.AtkCD_Ctr--;//冷却时间 
		}
		
		Process_SkillCD_MPRestore();
			
		if(!Flag_isSkilling)
		{
			if(!Remilia.Defense)
			{
				//控制处理 
				Process_PlayerSkill();
				Process_PlayerMoveRight();
				Process_PlayerMoveLeft();
				Process_PlayerJumpingUp();
				//动画处理 
				Anime_PlayerStand(Remilia.Flag_Direction);
				Anime_PlayerMove(Remilia.Flag_Direction);
				Anime_RemBeaten(Remilia.Flag_Direction);
			}
			else
			{
				Anime_PlayerDefense(Remilia.Flag_Direction);
			}
			Process_PlayerDefense();
		}
		if(Flag_isSkilling)
		{
			//技能A释放 
			Anime_RemiliaSkill_A(Remilia.Flag_Direction);
			//技能B释放 
			Anime_RemiliaSkill_B(Remilia.Flag_Direction);
			//普通攻击 
			Anime_RemNorAtk(Remilia.Flag_Direction);
			//大招
			Process_Remilia_Barrage();
		}
		if(!Remilia.Flag_Barrage)
			Process_PlayerDropDown();
		//处理Boss 
		Process_Boss();
		//技能B投射物飞行 
		Anime_RemSkillBArrow(Remilia_Skill_B.Flag_Direction);
		//敌人被攻击效果 
		Anime_RemSkill_HitBoss();
		//普通攻击效果 
		Anime_RemNorEft(Remilia.Flag_Direction);
		//player被Boss攻击效果
		Anime_RemBeatenBarrage();
		Anime_RemBeatenLaser();
		Anime_RemBeatenTentacle();
		//游戏胜利
		if(Boss.Flag_Death)
		{
			Anime_Boss_DeathEft();
			if(Boss.DeathEffect_Ctr > 25)
			{
				GUI_GameVictory();
				return(1);
			}
		} 
		//血条绘制 
		GUI_HpMp_bar();
		
		#ifdef ENABLE_Aux_Frame
		Frame_Player(Remilia);
		Frame_Boss(Boss);
		#endif
		
		//更新显示 
		delay_fps(System_DelayTime);
		//清屏 
		//cleardevice();
		putimage(0,0,WindowSize_L,WindowSize_H,Layer_Background,CurrentScreen_Xaxis,0);
	}
}

/************************************/
/*函数名：Process_Boss				*/
/*功  能：处理BOSS			 		*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Process_Boss(void)
{
	if(!Boss.Flag_Death)
	{
		if(!Boss.AtkCD_Ctr)
		{
			switch(Boss.SkillSelect)
			{
				case 1:
					if(BossAtk_Barrage_Flag)
						BossAtk_Barrage();
					break;
				case 2:
					Boss.isSilling = 1;
					BossAtk_Laser();
					break;
				case 3:
					Boss.isSilling = 1;
					BossAtk_Tentacle();
					break;
			}
		}
			
		Anime_BossActive();
	}
}

/************************************/
/*函数名：Anime_BossActive			*/
/*功  能：BOSS运动动画			 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_BossActive(void)
{
	double arc;
	
	if(Boss.AnimeAcitve_Ctr > 19)
	{
		Boss.AnimeAcitve_Ctr = 0;
	}
		
	//Boss Y_Axis Move 
	if(Boss.MoveSpeed_Ctr == Enemy_BossMove_Speed)
	{
		
		Boss.MoveSpeed_Ctr = 0;

		if(Boss.y > Boss.Target_Y)
		{
			Boss.y--;
		}
		else if(Boss.y < Boss.Target_Y)
		{
			Boss.y++;
		}

		Boss.Target_Y = Anime_BossMove_OffsetY;
	}
	Boss.MoveSpeed_Ctr++;
	
	putimage_withalpha(NULL,IMG_Boss[Boss.AnimeAcitve_Ctr],Boss.x - Anime_BossActive_OffsetX,Boss.y - Anime_BossActive_OffsetY);
	
	if(AnimeAcitve_SPCtr == Anime_BossActive_Speed)
	{
		AnimeAcitve_SPCtr = 0;
		Boss.AnimeAcitve_Ctr++;
	}
	AnimeAcitve_SPCtr++;
}

/************************************/
/*函数名：Anime_Boss_DeathEft		*/
/*功  能：BOSS死亡动画			 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
bool Anime_Boss_DeathEft(void)
{
	Boss.Flag_Death = 1;
	
	putimage_withalpha(NULL,IMG_BossDeath[Boss.DeathEffect_Ctr],Boss.x - 300,Boss.y - 110);
	
	if(!Boss.DeathEftSpeed_Ctr)
	{
		Boss.DeathEftSpeed_Ctr = Anime_BossDeath_Speed;
		Boss.DeathEffect_Ctr++;
	}
	if(Boss.DeathEftSpeed_Ctr > 0)
		Boss.DeathEftSpeed_Ctr--;
}

/************************************/
/*函数名：BossAtk_Barrage			*/
/*功  能：Boss弹幕技能			 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void BossAtk_Barrage(void)
{
	int i;
	int left,right,top,bottom;
	float damage;
	
	left = Remilia.x;
	right = Remilia.x + Remilia.Length;
	top = Remilia.y + 12;
	bottom = Remilia.y + 71;
	
	#ifdef ENABLE_Aux_Frame
		rectangle(left,top,right,bottom);
	#endif

	if(BossAtk_Barrage_Flag == -1)
	{
		switch(Boss.BarrageType)
		{
			case 1: BossAtk_BarrageInit_Type1(); break;
			case 2: BossAtk_BarrageInit_Type2(); break;
			case 3: BossAtk_BarrageInit_Type3(); break;
			case 4: BossAtk_BarrageInit_Type4(); break;
		}
		Boss.isSilling = 1;
	}

	BossAtk_Barrage_Flag = 0;

	for(i=0;i<BossAtk_Ctr_A;i++)
	{
		if(!BossBarrage_1[i].flag || !BossBarrage_2[i].flag)
		{	//加速度控制 
			if(!BossAtk_SpeedCtr)
			{
				switch(Boss.BarrageType)
				{
					case 1:
					case 2:
					case 4:
						if(BossBarrage_1[i].rad >= 0 && BossBarrage_1[i].rad < 100)
						{
							BossBarrage_1[i].rad += 5;
							BossBarrage_2[i].rad += 5;
							break;
						}
						if(BossBarrage_1[i].rad >= 100 && BossBarrage_1[i].rad < 200)
						{
							BossBarrage_1[i].rad += 4;
							BossBarrage_2[i].rad += 4;
							break;
						}
						if(BossBarrage_1[i].rad >= 200 && BossBarrage_1[i].rad < 350)
						{
							BossBarrage_1[i].rad += 3;
							BossBarrage_2[i].rad += 3;
							break;
						}
						else if(BossBarrage_1[i].rad >= 350)
						{
							BossBarrage_1[i].rad += 3;
							BossBarrage_2[i].rad += 3;
							break;
						}
					case 3:
						if(BossBarrage_1[i].rad >= 0 && BossBarrage_1[i].rad < 100)
						{
							BossBarrage_1[i].rad += 6;
							BossBarrage_2[i].rad += 5;
							break;
						}
						if(BossBarrage_1[i].rad >= 100 && BossBarrage_1[i].rad < 200)
						{
							BossBarrage_1[i].rad += 5;
							BossBarrage_2[i].rad += 4;
							break;
						}
						if(BossBarrage_1[i].rad >= 200 && BossBarrage_1[i].rad < 350)
						{
							BossBarrage_1[i].rad += 4;
							BossBarrage_2[i].rad += 3;
							break;
						}
						else if(BossBarrage_1[i].rad >= 350)
						{
							BossBarrage_1[i].rad += 3;
							BossBarrage_2[i].rad += 3;
							break;
						}
				}
				
				//坐标计算 
				Math_RotateAxis(&BossBarrage_1[i],0);
				Math_RotateAxis(&BossBarrage_2[i],0);
				
				//出界检测 
				if(BossBarrage_1[i].x < -20 || BossBarrage_1[i].y > 680 || BossBarrage_1[i].y < -20)
					BossBarrage_1[i].flag = 1;
				if(BossBarrage_2[i].x < -20 || BossBarrage_2[i].y > 680 || BossBarrage_2[i].y < -20)
					BossBarrage_2[i].flag = 1;
				
				//弹幕碰撞检测 1
				if(!Remilia.Flag_Barrage)
				if(BossBarrage_1[i].x + 16 >= left)
				if(BossBarrage_1[i].x + 16 <= right)
				if(BossBarrage_1[i].y + 16 >= top)
				if(BossBarrage_1[i].y + 16 <= bottom)
				{
					if(Music_BossBarrageHit.GetPlayStatus() == MUSIC_MODE_STOP)
						Music_BossBarrageHit.Play(0);//击中音效 
					
					if(!Remilia.Flag_Beaten)
						Remilia.Flag_Beaten = 1;
					Remilia.Flag_Direction = 1;
					if(!Remilia.BeatenBossBarrage_Ctr)
						Remilia.BeatenBossBarrage_Ctr = 1;//击中特效 
						
					//伤害计算 
					damage = random(BossAtk_Barrage_Damage)+1.0f - Remilia.Defense;
					if(damage < 0)
						damage = 0.02f;
				
					Remilia.HP -= damage;
					//删除弹幕 
					BossBarrage_1[i].flag = 1;
				}
				//弹幕碰撞检测 2
				if(!Remilia.Flag_Barrage)
				if(BossBarrage_2[i].x + 16 >= left)
				if(BossBarrage_2[i].x + 16 <= right)
				if(BossBarrage_2[i].y + 16 >= top)
				if(BossBarrage_2[i].y + 16 <= bottom)
				{
					if(Music_BossBarrageHit.GetPlayStatus() == MUSIC_MODE_STOP)
						Music_BossBarrageHit.Play(0);
						
					if(!Remilia.Flag_Beaten)
						Remilia.Flag_Beaten = 1;
					Remilia.Flag_Direction = 1;
					if(!Remilia.BeatenBossBarrage_Ctr)
						Remilia.BeatenBossBarrage_Ctr = 1;
						
					//伤害计算 
					damage = random(BossAtk_Barrage_Damage)+1.0f - Remilia.Defense;
					if(damage < 0)
						damage = 1;
						
					Remilia.HP -= damage;
					
					BossBarrage_2[i].flag = 1;
				}
			}
			
			//释放弹幕
			if(!BossBarrage_1[i].flag)
			{
				if(Music_BossBarrageFire.GetPlayStatus() == MUSIC_MODE_STOP)
				Music_BossBarrageFire.Play(0);
				putimage_withalpha(NULL,IMG_BossBarrage,BossBarrage_1[i].x,BossBarrage_1[i].y);
			}
			if(!BossBarrage_2[i].flag)
			{
				if(Music_BossBarrageFire.GetPlayStatus() == MUSIC_MODE_STOP)
				Music_BossBarrageFire.Play(0);
				putimage_withalpha(NULL,IMG_BossBarrage,BossBarrage_2[i].x,BossBarrage_2[i].y);
			}
			
			BossAtk_Barrage_Flag = 1;
		}
	}
	//释放结束 
	if(!BossAtk_Barrage_Flag)
	{
		BossAtk_Barrage_Flag = -1;
		BossAtk_Ctr_A = 0;
		BossAtk_Ctr_B = 0;
		Boss.BarrageType = random(4)+1;
		Boss.isSilling = 0;
	}
	//间隔计数器处理 
	if(BossAtk_Ctr_B == BossAtk_Barrage_Gap)
	{
		if(BossAtk_Ctr_A < BossAtk_Barrage_Density)BossAtk_Ctr_A++;
		BossAtk_Ctr_B = 0;
	}
	BossAtk_Ctr_B++;
	//速度计数器处理 
	if(BossAtk_SpeedCtr > 0)
		BossAtk_SpeedCtr--;
	else
		BossAtk_SpeedCtr = BossAtk_Barrage_Speed;
}

/************************************/
/*函数名：BossAtk_BarrageInit_Type1	*/
/*功  能：初始化Boss弹幕		 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void BossAtk_BarrageInit_Type1(void)
{
	int i = 0, j = 0, k = 0, z = 0;
	bool Direction_A = 0, Direction_B = 0;

	//初始化弹幕序列 
	j = BossAtk_Barrage_Ang_Start/BossAtk_Barrage_Ang_GapT1;
	z = BossAtk_Barrage_Ang_End/BossAtk_Barrage_Ang_GapT1;
	for(i=0;i<BossAtk_Barrage_Density;i++)
	{
		BossBarrage_1[i].arc = j * (AngleToArc_Value * BossAtk_Barrage_Ang_GapT1);//初始化角度
		BossBarrage_1[i].arc += AngleToArc_Value * k;//初始化摆动角 
		BossBarrage_1[i].rad = 0;
		BossBarrage_1[i].flag = 0;
		
		BossBarrage_2[i].arc = z * (AngleToArc_Value * BossAtk_Barrage_Ang_GapT1);//初始化角度
		BossBarrage_2[i].arc += AngleToArc_Value * k;//初始化摆动角 
		BossBarrage_2[i].rad = 0;
		BossBarrage_2[i].flag = 0;
		
		//初始角处理 
		if(j > BossAtk_Barrage_Ang_End/BossAtk_Barrage_Ang_GapT1)//7
			Direction_A = 0;
		else if(j < BossAtk_Barrage_Ang_Start/BossAtk_Barrage_Ang_GapT1)//5
			Direction_A = 1;
		
		if(Direction_A)
		{
			z--;
			j++;
		}
		else
		{
			j--;
			z++;
		}
			
		//摆动角处理
		if(Direction_B)
			k++;
		else
			k--;

		if(k > BossAtk_Barrage_Ang_Fluc)
			Direction_B = 0;
		else if(k < -BossAtk_Barrage_Ang_Fluc)
			Direction_B = 1;
	}
	
	BossAtk_Ctr_A = 1;
	BossAtk_Ctr_B = 1;
	BossAtk_Barrage_Flag = 1;
}

/************************************/
/*函数名：BossAtk_BarrageInit_Type2	*/
/*功  能：初始化Boss弹幕		 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void BossAtk_BarrageInit_Type2(void)
{
	int i = 0, j = 0, z = 0;

	//初始化弹幕序列 
	j = BossAtk_Barrage_Ang_Start/BossAtk_Barrage_Ang_GapT2;
	z = BossAtk_Barrage_Ang_End/BossAtk_Barrage_Ang_GapT2;
	
	for(i=0;i<BossAtk_Barrage_Density;i++)
	{
		BossBarrage_1[i].arc = j * (AngleToArc_Value * BossAtk_Barrage_Ang_GapT2);//初始化角度
		BossBarrage_1[i].rad = 0;
		BossBarrage_1[i].flag = 0;
		
		BossBarrage_2[i].arc = z * (AngleToArc_Value * BossAtk_Barrage_Ang_GapT2);//初始化角度
		BossBarrage_2[i].rad = 0;
		BossBarrage_2[i].flag = 0;
		
		//初始角处理 
		if(j > BossAtk_Barrage_Ang_End/BossAtk_Barrage_Ang_GapT2)//7
		{
			j = BossAtk_Barrage_Ang_Start/BossAtk_Barrage_Ang_GapT2; //5
			z = BossAtk_Barrage_Ang_End/BossAtk_Barrage_Ang_GapT2;	//7
		}

		z--;
		j++;
	}
	
	BossAtk_Ctr_A = 1;
	BossAtk_Ctr_B = 1;
	BossAtk_Barrage_Flag = 1;
}

/************************************/
/*函数名：BossAtk_BarrageInit_Type3	*/
/*功  能：初始化Boss弹幕		 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void BossAtk_BarrageInit_Type3(void)
{
	int i = 0, j = 0, z = 0;

	//初始化弹幕序列 
	j = BossAtk_Barrage_Ang_Start/BossAtk_Barrage_Ang_GapT3;
	z = BossAtk_Barrage_Ang_Start/BossAtk_Barrage_Ang_GapT3;
	
	for(i=0;i<BossAtk_Barrage_Density;i++)
	{
		BossBarrage_1[i].arc = j * (AngleToArc_Value * BossAtk_Barrage_Ang_GapT3);//初始化角度
		BossBarrage_1[i].rad = 0;
		BossBarrage_1[i].flag = 0;
		
		BossBarrage_2[i].arc = z * (AngleToArc_Value * BossAtk_Barrage_Ang_GapT3);//初始化角度
		BossBarrage_2[i].rad = 0;
		BossBarrage_2[i].flag = 0;
		
		//初始角处理 
		if(j > BossAtk_Barrage_Ang_End/BossAtk_Barrage_Ang_GapT3)	//7
		{
			j = BossAtk_Barrage_Ang_Start/BossAtk_Barrage_Ang_GapT3; 	//5
			z = BossAtk_Barrage_Ang_Start/BossAtk_Barrage_Ang_GapT3;	//5
		}

		z++;
		j++;
	}
	
	BossAtk_Ctr_A = 1;
	BossAtk_Ctr_B = 1;
	BossAtk_Barrage_Flag = 1;
}

/************************************/
/*函数名：BossAtk_BarrageInit_Type4	*/
/*功  能：初始化Boss弹幕		 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void BossAtk_BarrageInit_Type4(void)
{
	int i = 0, j = 0, z = 0;
	bool Direction_A = 0;

	//初始化弹幕序列 
	j = BossAtk_Barrage_Ang_Start/BossAtk_Barrage_Ang_GapT4;
	z = BossAtk_Barrage_Ang_End/BossAtk_Barrage_Ang_GapT4;
	
	for(i=0;i<BossAtk_Barrage_Density;i++)
	{
		BossBarrage_1[i].arc = j * (AngleToArc_Value * BossAtk_Barrage_Ang_GapT4);//初始化角度
		BossBarrage_1[i].rad = 0;
		BossBarrage_1[i].flag = 0;
		
		BossBarrage_2[i].arc = z * (AngleToArc_Value * BossAtk_Barrage_Ang_GapT4);//初始化角度
		BossBarrage_2[i].rad = 0;
		BossBarrage_2[i].flag = 0;
		
		//初始角处理 
		if(j > BossAtk_Barrage_Ang_End/BossAtk_Barrage_Ang_GapT4)//7
			Direction_A = 0;
		else if(j < BossAtk_Barrage_Ang_Start/BossAtk_Barrage_Ang_GapT4)//5
			Direction_A = 1;
		
		if(Direction_A)
		{
			z--;
			j++;
		}
		else
		{
			j--;
			z++;
		}
	}
	
	BossAtk_Ctr_A = 1;
	BossAtk_Ctr_B = 1;
	BossAtk_Barrage_Flag = 1;
}

/************************************/
/*函数名：BossAtk_Laser				*/
/*功  能：Boss激光技能			 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void BossAtk_Laser(void)
{
	putimage_withalpha(NULL,IMG_BossRing[BossAtk_Ctr_A],Boss.x - 48,Boss.y + 48);
	switch(BossAtk_Ctr_A)
	{
		case 0: 
			putimage_withalpha(NULL,IMG_BossLaser[BossAtk_Ctr_A],Boss.x - BossAtk_Laser_OffsetX,Boss.y + 76);
				Music_BossLaser.Play(0);
			break;
		case 1: putimage_withalpha(NULL,IMG_BossLaser[BossAtk_Ctr_A],Boss.x - BossAtk_Laser_OffsetX,Boss.y + 44); break;
		case 27: putimage_withalpha(NULL,IMG_BossLaser[BossAtk_Ctr_A],Boss.x - BossAtk_Laser_OffsetX,Boss.y + 44); break;
		case 28: putimage_withalpha(NULL,IMG_BossLaser[BossAtk_Ctr_A],Boss.x - BossAtk_Laser_OffsetX,Boss.y + 76); break;
		default: putimage_withalpha(NULL,IMG_BossLaser[BossAtk_Ctr_A],Boss.x - BossAtk_Laser_OffsetX,Boss.y - BossAtk_Laser_OffsetY);
	}

	if(BossAtk_Ctr_B == BossAtk_Laser_Speed)
	{
		//伤害判定 
		if(!Remilia.Flag_Barrage)
		if(BossAtk_Ctr_A > 1 && BossAtk_Ctr_A < 27)
		if(Remilia.y > Boss.y - 39 && Remilia.y < Boss.y + 197)
		{
			int damage;
			
			damage = BossAtk_Laser_Damage - Remilia.Defense;
			if(damage < 0)
				damage = 1;

			Remilia.HP -= damage;
			Remilia.Flag_Direction = 1;
			
			if(!Remilia.Flag_Beaten)
				Remilia.Flag_Beaten = 1;
				
			if(!Remilia.BeatenBossLaser_Ctr)
				Remilia.BeatenBossLaser_Ctr = 1;
		}
		
		//计数器处理 
		BossAtk_Ctr_A++;
		BossAtk_Ctr_B = 0;
	}
	BossAtk_Ctr_B++;

	if(BossAtk_Ctr_A > 28)
	{
		BossAtk_Ctr_A = 0;
		BossAtk_Ctr_B = 0;
		Boss.isSilling = 0;
	}
}

/************************************/
/*函数名：BossAtk_Tentacle			*/
/*功  能：Boss触手技能			 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void BossAtk_Tentacle(void)
{
	int i;
	float temp;
	bool flag=0;
	
	randomize();
	
	for(i=0;i<BossAtk_Tentacle_Amount;i++)
	{
		if(BossTentacle[i].x <= WindowSize_L+300)
		{
			flag = 1;
			putimage_withalpha(NULL,IMG_BossTentacle,BossTentacle[i].x,BossTentacle[i].y);
			
			if(!BossTentacle[i].musicflag)
			{
				Music_Tentacle.Play(0);
				BossTentacle[i].musicflag = 1;
			}
		
			temp = sqrt((BossTentacle[i].x + 310) / BossAtk_Tentacle_Speed);
		
			if(!BossTentacle[i].direction)
				BossTentacle[i].x -= temp;
			else
				BossTentacle[i].x += temp;
				
			if(BossTentacle[i].x < -200)
				BossTentacle[i].direction = 1;
				
			if(!Remilia.Flag_Barrage)
			if(!BossTentacle[i].atkflag && BossTentacle[i].x < Remilia.x && BossTentacle[i].y + 32 > Remilia.y && BossTentacle[i].y - 32 < Remilia.y + Remilia.Width)
			{
				Music_Blood.Play(0);
				BossTentacle[i].direction = 1;
				BossTentacle[i].damage = random(BossAtk_Tentacle_Damage) + 50;
				Remilia.HP -= BossTentacle[i].damage;
				BossTentacle[i].atkflag = 1;
				
				if(!Remilia.Flag_Beaten)
					Remilia.Flag_Beaten = 1;
				Remilia.Flag_Direction = 1;
				Remilia.BeatenBossTentacle_Ctr = 0;
			}
		}
	}
	
	if(!flag)
	{
		Boss.isSilling = 0;
		for(i=0;i<BossAtk_Tentacle_Amount;i++)
		{
			BossTentacle[i].musicflag = 0;
			BossTentacle[i].atkflag = 0;
			BossTentacle[i].direction = 0;
			BossTentacle[i].x = WindowSize_L + random(300);
			BossTentacle[i].y = random(WindowSize_H - 200);
		}
	}
}

/************************************/
/*函数名：Anime_RemBeatenLaser		*/
/*功  能：被Boss攻击效果		 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_RemBeatenTentacle(void)
{
	if(Remilia.BeatenBossTentacle_Ctr >= 0)
	{
		putimage_withalpha(NULL,IMG_Beaten_Tentacle[Remilia.BeatenBossTentacle_Ctr],Remilia.x - 12,Remilia.y);

		if(Remilia.BeatenBoss_Spd == Anime_SkillHitEffect_Speed)
		{
			Remilia.BeatenBoss_Spd = 0;
			Remilia.BeatenBossTentacle_Ctr++;
		}
		Remilia.BeatenBoss_Spd++;
		
		if(Remilia.BeatenBossTentacle_Ctr > 6)
		{
			Remilia.BeatenBoss_Spd = 0;
			Remilia.BeatenBossTentacle_Ctr = -1;
		}
	}
}


/************************************/
/*函数名：Anime_RemBeatenBarrage	*/
/*功  能：被Boss攻击效果		 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_RemBeatenBarrage(void)
{
	if(Remilia.BeatenBossBarrage_Ctr)
	{
		int OffsetX,OffsetY;
		OffsetX = Remilia.x - 12;
		OffsetY = Remilia.y;
		
		switch(Remilia.BeatenBossBarrage_Ctr)
		{
			case 1:
				putimage_withalpha(NULL,IMG_BarrageHitEffect,OffsetX,OffsetY,Anime_Barrage_HitEft_S1);
				break;
			case 2:
				putimage_withalpha(NULL,IMG_BarrageHitEffect,OffsetX,OffsetY,Anime_Barrage_HitEft_S2);
				break;
			case 3:
				putimage_withalpha(NULL,IMG_BarrageHitEffect,OffsetX,OffsetY,Anime_Barrage_HitEft_S3);
				break;
			case 4:
				putimage_withalpha(NULL,IMG_BarrageHitEffect,OffsetX,OffsetY,Anime_Barrage_HitEft_S4);
				break;
			case 5:
				putimage_withalpha(NULL,IMG_BarrageHitEffect,OffsetX,OffsetY,Anime_Barrage_HitEft_S5);
				break;
			case 6:
				putimage_withalpha(NULL,IMG_BarrageHitEffect,OffsetX,OffsetY,Anime_Barrage_HitEft_S6);
				break;
			case 7:
				putimage_withalpha(NULL,IMG_BarrageHitEffect,OffsetX,OffsetY,Anime_Barrage_HitEft_S7);
				break;
			case 8:
				putimage_withalpha(NULL,IMG_BarrageHitEffect,OffsetX,OffsetY,Anime_Barrage_HitEft_S8);
				Remilia.BeatenBoss_Spd = 0;
				Remilia.BeatenBossBarrage_Ctr = 0;
				break;
		}
		
		if(Remilia.BeatenBoss_Spd == Anime_SkillHitEffect_Speed)
		{
			Remilia.BeatenBoss_Spd = 0;
			Remilia.BeatenBossBarrage_Ctr++;
		}
		Remilia.BeatenBoss_Spd++;
	}
}

/************************************/
/*函数名：Anime_RemBeatenLaser		*/
/*功  能：被Boss攻击效果		 	*/
/*参  数：				 		 	*/
/*返回值： 		 					*/
/************************************/
void Anime_RemBeatenLaser(void)
{
	if(Remilia.BeatenBossLaser_Ctr)
	{
		int OffsetX,OffsetY;
		OffsetX = Remilia.x - 12;
		OffsetY = Remilia.y;
		
		switch(Remilia.BeatenBossLaser_Ctr)
		{
			case 1:
				putimage_withalpha(NULL,IMG_LaserHitEffect,OffsetX,OffsetY,Anime_Laser_HitEft_1);
				break;
			case 2:
				putimage_withalpha(NULL,IMG_LaserHitEffect,OffsetX,OffsetY,Anime_Laser_HitEft_2);
				break;
			case 3:
				putimage_withalpha(NULL,IMG_LaserHitEffect,OffsetX,OffsetY,Anime_Laser_HitEft_3);
				break;
			case 4:
				putimage_withalpha(NULL,IMG_LaserHitEffect,OffsetX,OffsetY,Anime_Laser_HitEft_4);
				break;
			case 5:
				putimage_withalpha(NULL,IMG_LaserHitEffect,OffsetX,OffsetY,Anime_Laser_HitEft_5);
				break;
			case 6:
				putimage_withalpha(NULL,IMG_LaserHitEffect,OffsetX,OffsetY,Anime_Laser_HitEft_6);
				break;
			case 7:
				putimage_withalpha(NULL,IMG_LaserHitEffect,OffsetX,OffsetY,Anime_Laser_HitEft_7);
				break;
			case 8:
				putimage_withalpha(NULL,IMG_LaserHitEffect,OffsetX,OffsetY,Anime_Laser_HitEft_8);
				break;
			case 9:
				putimage_withalpha(NULL,IMG_LaserHitEffect,OffsetX,OffsetY,Anime_Laser_HitEft_9);
				break;
			case 10:
				putimage_withalpha(NULL,IMG_LaserHitEffect,OffsetX,OffsetY,Anime_Laser_HitEft_10);
				break;
			case 11:
				putimage_withalpha(NULL,IMG_LaserHitEffect,OffsetX,OffsetY,Anime_Laser_HitEft_11);
				break;
			case 12:
				putimage_withalpha(NULL,IMG_LaserHitEffect,OffsetX,OffsetY,Anime_Laser_HitEft_12);
				Remilia.BeatenBoss_Spd = 0;
				Remilia.BeatenBossLaser_Ctr = 0;
				break;
		}
		
		if(Remilia.BeatenBoss_Spd == Anime_SkillHitEffect_Speed)
		{
			Remilia.BeatenBoss_Spd = 0;
			Remilia.BeatenBossLaser_Ctr++;
		}
		Remilia.BeatenBoss_Spd++;
	}
}

/************************************/
/*函数名： Math_Acceleration		*/
/*功  能： 计算加速度				*/	
/*参  数： 当前位置		 			*/
/*返回值： 增量△y		 			*/
/************************************/
int Math_Acceleration(int x)
{
	double y;
	
	y = sqrt(x);
	
	if((int)y==0)
		y = 1;
		
	return((int)y);
}

/************************************/
/*函数名： Math_RotateAngle			*/
/*功  能： 计算相对旋转弧度			*/	
/*参  数： 源对象坐标，目标对象坐标	*/
/*返回值： 旋转弧度		 			*/
/************************************/
double Math_RotateAngle(int x1,int y1,int x2,int y2)
{
	float a,b;
	
	a = abs(x1 - x2);
	b = abs(y1 - y2);
	
	if(y2 > y1)
	{
		if(x2 < x1)
			return(atan(b/a));
		else
			return(atan(a/b)+90*AngleToArc_Value);
	}
	else
	{
		if(x2 < x1)
			return(-atan(b/a));
		else
			return(-atan(a/b)-90*AngleToArc_Value);
	}
}

/************************************/
/*函数名：Math_RotateAxis			*/
/*功  能：极坐标换算直角坐标		*/	
/*参  数：弹幕指针					*/
/*返回值： 				 			*/
/************************************/
void Math_RotateAxis(Barrage_Parameter* p,bool com)
{
	if(!com)
	{
		p->x = p->rad * cos(p->arc) + Boss.x + 89;
		p->y = p->rad * sin(p->arc) + Boss.y + 89;
	}
	else
	{
		p->x = p->rad * cos(p->arc) + Remilia.x + 30;
		p->y = p->rad * sin(p->arc) + Remilia.y + 30;
	}
}

void Process_SkillCD_MPRestore(void)
{
	if(!Flag_isSkilling)
	{
		//回复MP 
		if(!MPRestore_Ctr)
		{
			if(Remilia.MP < Remilia_MP)
				Remilia.MP++;
			MPRestore_Ctr = RemMPRestore_Speed;
		}
		MPRestore_Ctr--;
		//技能冷却计数器处理
		if(NorAtk_CDcounter > 0)
			NorAtk_CDcounter--;
		if(SkillA_CDcounter > 0)
			SkillA_CDcounter--;
		if(SkillB_CDcounter > 0)
			SkillB_CDcounter--; 
		if(Barrage_CDcounter > 0)
			Barrage_CDcounter--;
	}
}

/************************************/
/*函数名： Frame_...				*/
/*功  能： 绘制对象碰撞框			*/	
/*参  数： 对象结构体				*/
/*返回值： 				 			*/
/************************************/
void Frame_Player(Player_Parameter Player)
{
	setcolor(0xFFFFFF);
	line( Player.x, Player.y, Player.x + Player.Length, Player.y);
	line( Player.x, Player.y + Player.Width, Player.x + Player.Length, Player.y + Player.Width);
	line( Player.x, Player.y, Player.x, Player.y + Player.Width);
	line( Player.x + Player.Length, Player.y, Player.x + Player.Length, Player.y + Player.Width);
}
void Frame_Enemy(Enemy_Parameter Enemy)
{
	setcolor(0xFFFFFF);
	line( Enemy.x, Enemy.y, Enemy.x + Enemy.Length, Enemy.y);
	line( Enemy.x, Enemy.y + Enemy.Width, Enemy.x + Enemy.Length, Enemy.y + Enemy.Width);
	line( Enemy.x, Enemy.y, Enemy.x, Enemy.y + Enemy.Width);
	line( Enemy.x + Enemy.Length, Enemy.y, Enemy.x + Enemy.Length, Enemy.y + Enemy.Width);
}
void Frame_Boss(Boss_Parameter BOSS)
{
	setcolor(0xFFFFFF);
	line( BOSS.x, BOSS.y, BOSS.x + BOSS.Length, BOSS.y);
	line( BOSS.x, BOSS.y + BOSS.Width, BOSS.x + BOSS.Length, BOSS.y + BOSS.Width);
	line( BOSS.x, BOSS.y, BOSS.x, BOSS.y + BOSS.Width);
	line( BOSS.x + BOSS.Length, BOSS.y, BOSS.x + BOSS.Length, BOSS.y + BOSS.Width);
}

/************************************/
/*函数名： Debug_BinOutput			*/
/*功  能： 输出二进制数	 			*/
/*参  数： longlong					*/
/*返回值： 		 					*/
/************************************/
void Debug_BinOutput(long long number)
{
	char string[64];
	
	itoa(number,string,2);
	printf("%64s\n",string);
}

void SYS_GetMouse(void)
{
	if(mousemsg())
	{
		Temp_Mouse = getmouse();
		
		Mouse.x = Temp_Mouse.x;
		Mouse.y = Temp_Mouse.y;
		Mouse.wheel = Temp_Mouse.wheel;
		Mouse.is_left = Temp_Mouse.is_left();
		Mouse.is_wheel = Temp_Mouse.is_wheel();
	}
	
}

void SYS_Speed(void)
{
	if(Mouse.is_wheel)
	{
		Mouse.is_wheel = 0;
		
		if(Mouse.wheel > 0)
		{
			if(System_DelayTime < 1000)
			{
				System_DelayTime++;
			}
		}
		else
		{
			if(System_DelayTime > 120)
			{
				System_DelayTime--;
			}
		}
		
		stream = fopen("Data\\system","w+");
		fprintf(stream,"%d\n",System_DelayTime);
		fclose(stream);
		printf("%d\n",System_DelayTime);
		Mouse.wheel = 0;
	}
	
}

/************************************/
/*函数名： SYS_debug				*/
/*功  能： 调试函数		 			*/
/*参  数： 		 					*/
/*返回值： 		 					*/
/************************************/
void SYS_debug(void)
{
 int x = x;
}

