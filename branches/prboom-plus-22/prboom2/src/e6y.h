#ifndef __E6Y__
#define __E6Y__

#include "hu_lib.h"
#include "SDL_timer.h"
#include "SDL_events.h"

#define MF_RESSURECTED  (uint_64_t)(0x0000001000000000)

#define HU_HUDADDX (HU_HUDX)
#define HU_HUDADDY (HU_HUDY+(-1)*HU_GAPY)
#define HU_CENTERMSGX (320/2)
#define HU_CENTERMSGY ((200-ST_HEIGHT)/2 - 1 - SHORT(hu_font[0].height))

#define HU_HUDADDX_D (HU_HUDX_LL)
#define HU_HUDADDY_D (HU_HUDY_LL+(-1)*HU_GAPY)

#define HU_MSGCENTERTIMEOUT   (2*TICRATE)

#define STSTR_SECRETFOUND   "A secret is revealed!"

#define MAXINTERPOLATIONS 2048

#define S_CANT_GL_ARB_MULTITEXTURE 0x10000000
#define S_CANT_GL_ARB_MULTISAMPLEFACTOR  0x20000000

#define E6Y_CALC_TEX_VALUES_MIDDLE2S(w, seg, peg, linelength, lineheight, deltaceiling, deltafloor)\
  (w).flag=GLDWF_M2S;\
  (w).ul=OU((w),(seg))+(0.0f);\
  (w).ur=OU((w),(seg))+((linelength)/(float)(w).gltexture->buffer_width);\
  (w).vt=deltaceiling/(w).gltexture->realtexheight;\
  (w).vb=1.0f-deltafloor/(w).gltexture->realtexheight;

#define GL_COMBINE_ARB                    0x8570
#define GL_RGB_SCALE_ARB                  0x8573

#define NO_INDEX ((unsigned short)-1)

#define FOV_CORRECTION_FACTOR (1.13776f)
#define FOV90 (90)

#define E_ST_X 284

typedef struct
{
  const char *wadname;
  int map;
  int address;
} buf_overrun_item_t;

typedef struct camera_s
{
  long x;
  long y;
  long z;
  long PrevX;
  long PrevY;
  long PrevZ;
  angle_t angle;
  angle_t pitch;
  angle_t PrevAngle;
  angle_t PrevPitch;
  int type;
} camera_t;

extern boolean wasWiped;

extern int totalleveltimes;

extern int secretfound;
extern int messagecenter_counter;
extern int demo_skiptics;
extern int demo_recordfromto;

extern int avi_shot_count;
extern int avi_shot_time;
extern int avi_shot_num;
extern const char *avi_shot_fname;
extern char avi_shot_curr_fname[PATH_MAX];

extern FILE    *_demofp;
extern boolean doSkip;
extern boolean demo_stoponnext;
extern boolean demo_stoponend;
extern boolean demo_warp;

extern int key_speed_up;
extern int key_speed_down;
extern int key_speed_default;
extern int key_demo_jointogame;
extern int key_demo_nextlevel;
extern int key_demo_endlevel;
extern int speed_step;
extern int key_walkcamera;

extern int hudadd_gamespeed;
extern int hudadd_leveltime;
extern int hudadd_secretarea;
extern int hudadd_smarttotals;
extern int movement_mouselook;
extern int movement_mouseinvert;
extern int movement_strafe50;
extern int movement_strafe50onturns;
extern int movement_smooth;
extern int movement_altmousesupport;
extern int render_fov;
extern int render_usedetail;
extern int render_detailwalls;
extern int render_detailflats;
extern int render_detailsprites;
extern int render_usedetailwalls;
extern int render_usedetailflats;
extern int render_usedetailsprites;
extern int render_multisampling;
extern int render_smartitemsclipping;
extern int render_wipescreen;
extern int mouse_acceleration;
extern int demo_smoothturns;
extern int demo_smoothturnsfactor;
extern int demo_overwriteexisting;
extern int misc_fixfirstmousemotion;
extern int misc_spechitoverrun_warn;
extern int misc_rejectoverrun_warn;
extern int misc_rejectoverrun_emulate;
extern int misc_spechitoverrun_emulate;

extern int test_sky1;
extern int test_sky2;

extern int palette_ondamage;
extern int palette_onbonus;
extern int palette_onpowers;

extern camera_t walkcamera;
extern mobj_t *oviewer;

extern fixed_t sidemove_normal[2];
extern fixed_t sidemove_strafe50[2];

extern fixed_t r_TicFrac;
extern int otic;
extern boolean NewThinkerPresent;

extern fixed_t oviewx;
extern fixed_t oviewy;
extern fixed_t oviewz;
extern angle_t oviewangle;
extern angle_t oviewpitch;

extern int PitchSign;
extern int mouseSensitivity_mlook;
extern angle_t viewpitch;
extern float fovscale;
extern float maxNoPitch[];
extern float tan_pitch;
extern float skyUpAngle;
extern float skyUpShift;
extern float skyXShift;
extern float skyYShift;

extern boolean SkyDrawed;

extern boolean isExtraDDisplay;
extern boolean skipDDisplay;
extern unsigned int DDisplayTime;
extern unsigned int TicStart;
extern unsigned int TicNext;
extern float TicksInMSec;

extern float internal_render_fov;

extern boolean gl_arb_multitexture;
extern int idDetail;

extern hu_textline_t  w_hudadd;
extern hu_textline_t  w_centermsg;
extern char hud_timestr[80];
extern char hud_centermsg[80];

void e6y_assert(const char *format, ...);

void e6y_D_DoomMainSetup(void);
void e6y_I_Init(void);

void P_WalkTicker ();
void P_ResetWalkcam ();

void e6y_I_uSleep(unsigned long usecs);
void G_SkipDemoStart(void);
void G_SkipDemoStop(void);
const byte* G_ReadDemoHeader(const byte* demo_p);
void M_ChangeAltMouseHandling(void);
void M_ChangeSmooth(void);
void M_ChangeDemoSmoothTurns(void);
void M_ChangeSpeed(void);
void M_ChangeMouseLook(void);
void M_ChangeMouseInvert(void);
void M_ChangeFOV(void);
void M_ChangeUseDetail(void);
void M_ChangeMultiSample(void);
void M_MouseMLook(int choice);
void M_MouseAccel(int choice);
void CheckPitch(signed int *pitch);
void I_Init2(void);
void D_Display(void);
boolean GetMouseLook(void);

void Extra_D_Display(void);
fixed_t I_GetTimeFrac (void);
void I_GetTime_SaveMS(void);
void R_InterpolateView (player_t *player, fixed_t frac);

typedef enum
{
  INTERP_SectorFloor,
  INTERP_SectorCeiling,
  INTERP_Vertex
} EInterpType;

typedef struct FActiveInterpolation_s
{
  EInterpType Type;
  void *Address;
} FActiveInterpolation;

extern int numinterpolations;
extern int startofdynamicinterpolations;
extern fixed_t oldipos[MAXINTERPOLATIONS][1];
extern fixed_t bakipos[MAXINTERPOLATIONS][1];
extern FActiveInterpolation curipos[MAXINTERPOLATIONS];
extern boolean NoInterpolateView;
extern boolean r_NoInterpolate;

void R_ResetViewInterpolation ();
void CopyInterpToOld (int i);
void CopyBakToInterp (int i);
void DoAnInterpolation (int i, fixed_t smoothratio);
void updateinterpolations();
void setinterpolation(EInterpType type, void *posptr);
void stopinterpolation(EInterpType type, void *posptr);
void stopallinterpolation(void);
void dointerpolations(fixed_t smoothratio);
void restoreinterpolations();
void P_ActivateAllInterpolations();
void SetInterpolationIfNew(thinker_t *th);
void StopInterpolationIfNeeded(thinker_t *th);

#ifdef GL_DOOM

#define DETAIL_DISTANCE 9

typedef struct tagTAnimItemParam
{
  int count;
  int index;
} TAnimItemParam;

extern float xCamera,yCamera;
extern TAnimItemParam *anim_flats;
extern TAnimItemParam *anim_textures;

float distance2piece(float x0, float y0, float x1, float y1, float x2, float y2);
void e6y_InitExtensions(void);
void e6y_PreprocessLevel(void);
void MarkAnimatedTextures(void);

#endif //GL_DOOM

#define MAX_DEMOS_SMOOTHFACTOR 16 
extern const byte *demo_p_end;
extern int playerscount;
void e6y_ProcessDemoHeader(void);
void ClearSmoothViewAngels();
void AddSmoothViewAngel(int delta);
angle_t GetSmoothViewAngel(angle_t defangle);
void e6y_AfterTeleporting(void);

extern float viewPitch;
extern boolean WasRenderedInTryRunTics;
extern boolean trasparentpresent;

#define MAPBITS 12
#define FRACTOMAPBITS (FRACBITS-MAPBITS)

void R_ClearClipSegs (void);
void R_RenderBSPNode(int bspnum);
void R_SetupFrame (player_t *player);

void e6y_MultisamplingCheck(void);
void e6y_MultisamplingSet(void);
void e6y_MultisamplingPrint(void);

void I_Warning(const char *error, ...);

extern int force_monster_avoid_hazards;

int StepwiseSum(int value, int direction, int step, int minval, int maxval, int defval);

boolean StrToInt(char *s, long *l);

void CheckForSpechitsOverrun(line_t* ld);
void SwitchToGameWindow(void);

enum
{
  TT_ALLKILL,
  TT_ALLITEM,
  TT_ALLSECRET,

  TT_TIME,
  TT_TOTALTIME,
  TT_TOTALKILL,
  TT_TOTALITEM,
  TT_TOTALSECRET,

  TT_MAX
};

typedef struct timetable_s
{
  char map[16];

  int kill[MAXPLAYERS];
  int item[MAXPLAYERS];
  int secret[MAXPLAYERS];
  
  int stat[TT_MAX];
/*  int allkill;
  int allitem;
  int allsecret;

  int time;
  int totaltime;
  int totalkill;
  int totalitem;
  int totalsecret;*/
} timetable_t;

extern int stats_level;
void e6y_G_DoCompleted(void);
void e6y_G_CheckDemoStatus(void);
void e6y_WriteStats(void);

void e6y_G_DoWorldDone(void);

void e6y_I_GetEvent(void);
void CenterMouse_Win32(long x, long y);
void GrabMouse_Win32(void);
void UngrabMouse_Win32(void);
void e6y_I_InitInputs(void);
int AccelerateMouse(int val);
void MouseAccelChanging(void);

extern int rjlen;
extern int rjreq;
void AddIntForRejectOverflow(int k);

extern int mlooky;
extern int realtic_clock_rate;
extern boolean IsDehMaxHealth;
extern int maxhealthbonus;
extern int deh_maxhealth;
void e6y_G_Compatibility(void);

extern boolean zerotag_manual;
extern int comperr_zerotag;
extern int comperr_passuse;

boolean compbad_get(int *compbad);
//boolean CompErrZeroTag(void);
//boolean CompErrPassUse(void);

int G_GetOriginalDoomCompatLevel(int ver);

boolean ProcessNoTagLines(line_t* line, sector_t **sec, int *secnum);

//extern int viewMaxY;

/*typedef struct tagTREC
{
  int index;
  int health;
} TRec;
extern int t_count;
extern TRec t_list[];*/

#endif
