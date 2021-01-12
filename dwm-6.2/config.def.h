/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 5, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 25;       /* snap pixel */

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 24;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 24;       /* horizontal padding of bar */
static const char buttonbar[]       = "  " ;

static const char *fonts[]          = { "mono hack:size=11" , "fontawesome:size=11" };
static const char dmenufont[]       = "monospace:size=10";

static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_urgborder[]   = "#ff0000";

static const char col_drBackground[] = "#282a36";
static const char col_drSelection[]  = "#44475a";
static const char col_drForeground[] = "#f8f8f2";
static const char col_drComment[]    = "#6272a4";
static const char col_drCyan[]       = "#8be9fd";
static const char col_drGreen[]      = "#50fa7b";
static const char col_drOrange[]     = "#ffb86c";
static const char col_drPink[]       = "#ff79c6";
static const char col_drPurple[]     = "#bd93f9";
static const char col_drRed[]        = "#ff5555";
static const char col_drYellow[]     = "#f1fa8c";

static const char *colors[][3]       = {
	/*                    fg                bg                border   */
	[SchemeNorm]      = { col_drForeground, col_drBackground,  col_drBackground },
	[SchemeSel]       = { col_drForeground, col_drBackground,  col_drGreen      },
	[SchemeStatus]    = { col_drForeground, col_drBackground,  "#000000"        }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]   = { col_drForeground, col_drPurple,     "#000000"        }, // Tagbar left selected {text,background,not used but cannot be empty}
  [SchemeTagsNorm]  = { col_drForeground, col_drBackground,  "#000000"        }, // Tagbar left unselected {text,background,not used but cannot be empty}
  [SchemeInfoSel]   = { col_drForeground, col_drBackground,  "#000000"        }, // infobar middle  selected {text,background,not used but cannot be empty}
  [SchemeInfoNorm]  = { col_drForeground, col_drBackground,  "#000000"        }, // infobar middle  unselected {text,background,not used but cannot be empty}
	[SchemeUrg]  = { col_gray4, col_cyan,  col_urgborder  },
};

/* tagging */
static const char *tags[] = { "  ", "  ", "  ", " ", "  ", "  ", "  ", "  " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Signal",   NULL,       NULL,       1 << 6,       0,           -1 },
	{ "Spotify",  NULL,       NULL,       1 << 5,       0,           -1 },
	{ "discord",  NULL,       NULL,       1 << 4,       0,           -1 },
	{ "Steam",	  NULL,       NULL,       1 << 3,       0,           -1 },
	{ "st",				NULL,       NULL,       1 << 2,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
	{ NULL,       NULL },
};


/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* commands */
static char dmenumon[2] = "0";  /* component of dmenucmd, manipulated in spawn() */ 
static const char *dmenucmd[]		= { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_drBackground, "-nf", col_drForeground, "-sb", col_drComment, "-sf", col_drForeground, NULL }; 
static const char *roficmd[]	  = { "/home/cmdctrll/.config/rofi/launchers/misc/launcher.sh", NULL };
static const char *powermcmd[]  = { "/home/cmdctrll/.config/rofi/applets/applets/powermenu.sh", NULL };
static const char *termcmd[]		= { "st", NULL };

/* More functions */
static const char *bravecmd[]				=			{ "brave", "--new-window", NULL };
static const char *discordcmd[]			=			{ "discord", NULL };
static const char *spotifycmd[]		  =			{ "spotify", NULL };
static const char *ncmpcppcmd[]			=			{ "st" , "ncmpcpp", NULL };
static const char *pulsemixercmd[]  =			{ "st" , "pulsemixer", NULL };
static const char *coincmd[]		  =		  { "st" , "cointop", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
/*	{ MODKEY,                     XK_d,			 spawn,					 {.v = dmenucmd } }, */
	{ MODKEY,												XK_r,			 spawn,					 {.v = roficmd } },
	{ MODKEY,												XK_p,			 spawn,					 {.v = powermcmd } },
	{ MODKEY,												XK_Return, spawn,					 {.v = termcmd } },
	{ MODKEY|ShiftMask,							XK_m,			 spawn,					 {.v = pulsemixercmd } },
	{ MODKEY,												XK_m,			 spawn,					 {.v = ncmpcppcmd } },
	{ MODKEY|Mod1Mask,							XK_m,			 spawn,					 {.v = spotifycmd} },
	{ MODKEY|ShiftMask,							XK_b,			 spawn,					 {.v = coincmd} },
	{ MODKEY,												XK_period, spawn,				   SHCMD("mpc next" ) },
	{ MODKEY,												XK_comma,  spawn,					 SHCMD("mpc prev" ) },
	{ MODKEY|Mod1Mask,							XK_Up,		 spawn,					 SHCMD("pamixer --allow-boost -i 10; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|Mod1Mask,							XK_Down,   spawn,					 SHCMD("pamixer --allow-boost -d 10; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|Mod1Mask,						  XK_Right,  spawn,					 SHCMD("playerctl next") },
	{ MODKEY|Mod1Mask,							XK_Left,	 spawn,					 SHCMD("playerctl previous") },
	{ MODKEY|Mod1Mask,							XK_space,  spawn,					 SHCMD("playerctl play-pause") },
	{ MODKEY,												XK_b,			 spawn,					 {.v = bravecmd } },
	{ MODKEY,												XK_c,			 spawn,					 {.v = discordcmd } },
	{ MODKEY|ControlMask,           XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ControlMask,           XK_q,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_w,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_e,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ControlMask,           XK_y,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ControlMask,           XK_u,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ControlMask,           XK_space,  setlayout,      {0} },
	{ MODKEY|ControlMask,						XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Left,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_Right,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,  tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,           XK_d,			 setgaps,        {.i = -5 } },
	{ MODKEY|ControlMask,           XK_a,  	   setgaps,        {.i = +5 } },
	{ MODKEY|ControlMask,           XK_s,  	   setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ControlMask,           XK_g,			 setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkButton,						0,							Button1,				spawn,					{.v = powermcmd } }, 
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

