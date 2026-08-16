#ifndef __MGS_G_EXTERN_H__
#define __MGS_G_EXTERN_H__

/*---------------------------------------------------------------------------*/

/* gamed.c */
extern int GM_GameStatus;
extern int GM_LoadRequest;
extern int GM_GameOverTimer;
extern SVECTOR *GM_lpsvectWind;
extern int (*GM_lpfnPlayerActControl)(GV_ACT *);
extern int (*GM_lpfnPlayerActObject2)(GV_ACT *);
extern short GM_uBombHoming;
extern short GM_uTenageMotion;
extern int (*GM_lpfnBombHoming)(CONTROL *, int, int *);
extern int (*GM_lpfnBombBound)(int, CONTROL *, int *);
extern int (*GM_lpfnBombExplosion)(TARGET *, int);
extern int GM_PadResetDisable;

#ifndef __GAME_GAMED_C__
//extern char    *GM_StageName;
//extern GV_PAD  *GM_CurrentPadData;
extern int      dword_800AB9D4;
extern short    GM_WeaponChanged;
extern int      GM_ClaymoreMap;
extern int      GM_AlertMax;
extern unsigned int GM_DisableWeapon;
extern int      gTotalFrameTime;
extern short    GM_Magazine;
extern int      GM_PlayerAddress;
extern CONTROL *GM_PlayerControl;
extern SVECTOR  GM_NoisePosition;
extern int      GM_AlertMode;
extern int      GM_Photocode;
//extern int dword_800ABA08;
extern int      GM_PlayerMap;
extern SVECTOR  GM_PlayerPosition;
extern int      GM_AlertLevel;
extern int      dword_800ABA1C;
extern OBJECT  *GM_PlayerBody;
extern int      GM_NoisePower;
extern int      GM_DisableItem;
extern short    GM_MagazineMax;
extern int      GM_NoiseLength;
extern short    GM_O2;
extern short    GM_PDA_ClearRank;
extern int      GM_LoadComplete;
extern int      GM_PadVibration;
extern int      GM_PlayerAction;
extern SVECTOR  GM_PhotoViewPos;
extern PlayerStatusFlag GM_PlayerStatus;
extern int      GM_PadVibration2;
#endif // __GAME_GAMED_C__

/*---------------------------------------------------------------------------*/

/* gamed.c */
void GM_InitReadError(void);
void DrawReadError(void);
void GM_SetSystemCallbackProc(int index, int proc);
void GM_CallSystemCallbackProc(int id, int arg);
void GM_SetLoadCallbackProc(int);
void GM_ContinueStart(void);
void GM_GameOver(void);
void GM_StartDaemon(void);

/* script.c */
int  GM_ResetScript(void);
void GM_InitScript(void);

/* area.c */
void GM_InitArea(void);
void GM_GetAreaHistory(AreaHistory *pHistoryCopy);
void GM_SetAreaHistory(AreaHistory *pNewHistory);
int  GM_SetArea(int stage_id, char *stage_name);
int  GM_AreaHistory(int stage_id);
char *GM_GetArea(int flag);

/* chara.c */
void GM_InitChara(void);
void GM_ResetChara(void);
void *GM_GetChara(unsigned char *script);
void *GM_GetCharaID(int chara_id);

/* alert.c */
void GM_SetSong(int song);
int  GM_GetNoiseSound(int flag, int noise);
void GM_SoundStart(void);
void GM_AlertSound(void);
void GM_AlertReset(void);
void GM_AlertAct(void);
void GM_AlertModeSet(int mode);
void GM_AlertModeInit(void);
void GM_AlertModeReset(void);

/* g_sound.c */
void GM_SeSet(SVECTOR *pos, int se_id);
void GM_SeSet2(int pan, int vol, int se_id);
void GM_SeSetMode(SVECTOR *pos, int se_id, int mode);
void GM_SeSet3(int pan, int vol, int se_id);
void GM_SeSetPan(SVECTOR *pos, int se_id, int vol);
void GM_SeSetSize(SVECTOR *pos, int se_id, int size);
void GM_SetSound(int sound_code, int sync_mode);

/* object.c */
void GM_InitObjectNoRots(OBJECT_NO_ROTS *obj, int model, int flag, int motion);
void GM_InitObject(OBJECT *obj, int model, int flag, int motion);
void GM_ActMotion(OBJECT *obj);
void GM_ActObject(OBJECT *obj);
void GM_ActObject2(OBJECT *obj);
void GM_FreeObject(OBJECT *obj);
void GM_ConfigObjectFlags(OBJECT *obj, int flags);
void GM_ConfigObjectLight(OBJECT *obj, MATRIX *light);
void GM_ConfigObjectStep(OBJECT *obj, SVECTOR *step);
void GM_ConfigObjectRoot(OBJECT *obj, OBJECT *parent_obj, int num_parent);
void GM_ConfigObjectJoint(OBJECT *obj);
void GM_ConfigObjectSlide(OBJECT *obj);

void GM_ConfigObjectAction(OBJECT *obj, int action, int frame, int interp);
void GM_ConfigObjectOverride(OBJECT *obj, int action, int frame, int interp, u_long mask);
int  GM_ConfigObjectMotion(OBJECT *obj, int action_flag, int motion);

int  GM_ConfigObjectModel(OBJECT_NO_ROTS *obj, int model);

/* control.c */
void GM_InitWhereSystem(void);
int  GM_InitControl(CONTROL *control, int scriptData, int scriptBinds);
void GM_ActControl(CONTROL *control);
void GM_FreeControl(CONTROL *control);
void GM_ConfigControlVector(CONTROL *ctrl, SVECTOR *mov, SVECTOR *rot);
void GM_ConfigControlMatrix(CONTROL *control, MATRIX *world);
void GM_ConfigControlString(CONTROL *control, char *mov, char *rot);
void GM_ConfigControlHazard(CONTROL *ctrl, int height, int r_sphere, int s_sphere);
void GM_ConfigControlAttribute(CONTROL *control, int atr);
void GM_ConfigControlInterp(CONTROL *control, int interp);
int  GM_CheckControlTouches(CONTROL *control, int range);
void GM_ConfigControlRadarparam(CONTROL *ctrl, u_short dir, u_short dis, int range, u_short r);
void GM_ConfigControlTrapCheck(CONTROL *control);
GV_MSG *GM_CheckMessage(void *work, int name, int msgcode);

/* motion.c */
int  GM_ConfigMotionControl(OBJECT *object, MOTION_CONTROL *m_ctrl, int name,
                            MOTION_SEGMENT *m_segs1, MOTION_SEGMENT *m_segs2,
                            CONTROL *control, SVECTOR *rots);
int  GM_ConfigMotionAdjust(OBJECT *object, SVECTOR *adjust);
void GM_ConfigAction(MOTION_CONTROL *m_ctrl, int action, int frame);
void GM_ConfigActionOverride(MOTION_CONTROL *m_ctrl, int action, int frame);
int  GM_PlayAction(MOTION_CONTROL *m_ctrl);

/* map.c */
MAP *GM_FindMap(int name);
int  GM_AddMap(int name);
int  GM_DelMap(int name);
MAP *GM_GetMap(int id);
MAP *GM_DefineMap(void);
int  GM_ReloadMap(int preshade);
void GM_UpdateMap(void);
void GM_ResetMap(void);
HZD_HDL *GM_IterHazard(HZD_HDL *cur);
void GM_ResetMapHazard(void);
void GM_ResetMapModel(void);
MAP *GM_FindMapZone(int zone);
MAP *GM_CreateMap(void);
void GM_ReshadeObjs(DG_OBJS *objs);
void GM_ReshadeMapAll(void);

/* target.c */
void    GM_InitTargetSystem(void);
TARGET *GM_AllocTarget(void);
void    GM_FreeTarget(TARGET *target);
void    GM_MoveTarget(TARGET *target, SVECTOR *pVec);
TARGET *GM_CaptureTarget(TARGET *target);
TARGET *GM_C4Target(TARGET *target);
int     GM_TouchTarget(TARGET *target);
int     GM_PowerTarget(TARGET *target);
int     GM_PushTarget(TARGET *target);
void    GM_SetTarget(TARGET *target, int class, int side, SVECTOR *size);
void    GM_SetCaptureTarget(TARGET *target, int a_mode, int faint, int *a4, SVECTOR *a5);
void    GM_SetPowerTarget(TARGET *target, int p_mode, int a_mode, int vital, int faint, SVECTOR *force);
void    GM_TargetBody(TARGET *target, MATRIX *body) ;
int     GM_OnlineTargetCheck(SVECTOR *from, SVECTOR *to, int map, SVECTOR *hit, int side);
int     GM_OnlineTargetCheckAny(SVECTOR *from, SVECTOR *to, int map, SVECTOR *hit);
void    GM_GetTargets(int *count, TARGET **targets);

/* homing.c */
void    GM_ResetHomingTargets(void);
HOMING *GM_AllocHomingTarget(MATRIX *world, CONTROL *control);
void    GM_FreeHomingTarget(HOMING *hom);
void    GM_GetHomingTarget(MATRIX *world, int ang, int *yaw, int *pitch, int map);
void    GM_GetHomingTarget2(MATRIX *world, int ang, int *yaw, int *pitch, int map, int max_dist, int max_ang);

/*---------------------------------------------------------------------------*/
#endif // __MGS_G_EXTERN_H__
