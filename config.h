/* See LICENSE file for copyright and license details. */

/* appearance */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const int showbar            = 1;        /* 0 means no bar */
static const int showsystray        = 1;        /* 0 means no systray */
static const int startontag         = 1;        /* 0 means no tag active on start */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const unsigned int systrayspacing = 2;   /* systray spacing */

static const char *fonts[]          = { "Homebrew 7x12 CS:size=9", "Symbols Nerd Font:size=11" };

static char normbgcolor[]           = "#282c34";
static char normbordercolor[]       = "#282c34";
static char normfgcolor[]           = "#abb2bf";
static char selfgcolor[]            = "#282c34";
static char selbordercolor[]        = "#61afef";
static char selbgcolor[]            = "#61afef";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
        [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
        [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "", "󰈹", "󰈙", "󰆋", "󰓇" };
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */

    // Tiled
	/* class           instance       title                tags mask  isfloating  isfreesize  monitor */
	{ "firefox",       NULL,          NULL,                1 << 2,    0,          0, -1 },
	{ "Joplin",        NULL,          NULL,                1 << 3,    0,          0, -1 },
     // { "okular",        NULL,          NULL,                1 << 3,    0,          0, -1 },
     // { "Pcmanfm",       NULL,          NULL,                1 << 4,    0,          0, -1 },
	{ "Spotify",       NULL,          NULL,                1 << 5,    0,          0,  1 },

    //Floating
	{ "Gnome-2048",    NULL,          NULL,                0,         1,          1, -1 },
	{ "VirtualBoxVM",  NULL,          "Keyboard",          0,         1,          1, -1 },
	{ "solvespace",    NULL,          "Property Browser",  0,         1,          1, -1 },
	{ NULL,            "matplotlib",  NULL,                0,         1,          1, -1 },

    // Misc
	{ "Microsoft",     NULL,          NULL,                0,         0,          0, -1 },
	{ "St",            NULL,          NULL,                0,         0,          0, -1 },
      //{ "Minecraft 1.12.2",  NULL,     NULL,                1 << 7,    0,           0, 1 },

};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "###",      nrowgrid },
	{ "|M|",      centeredmaster },
	{ NULL,       NULL },

	// { "[\\]",     dwindle },
	// { "===",      bstackhoriz },
	// { "HHH",      grid },
	// { "---",      horizgrid },
	// { ":::",      gaplessgrid },
	// { ">M>",      centeredfloatingmaster },
	// { "><>",      NULL },    /* no layout function means floating behavior */
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

static const char *termcmd[]  = { "st", NULL };

static const char *rofidrun[] = { "rofi", "-show", "drun" };
static const char *rofirun[] = { "rofi", "-show", "run" };
 
#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */

	{ MODKEY,            		XK_g,      cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_g,      cyclelayout,    {.i = -1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_w,      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_w,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_g,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_g,      incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY|ControlMask,           XK_j,      pushdown,       {0} },
	{ MODKEY|ControlMask,           XK_k,      pushup,         {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_m,      zoom,           {0} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ 0,                       XF86XK_AudioRaiseVolume, spawn, SHCMD("pamixer -i 3") },
	{ 0,                       XF86XK_AudioLowerVolume, spawn, SHCMD("pamixer -d 3") },
	{ 0,                       XF86XK_AudioMute,        spawn, SHCMD("pamixer -t") },
	{ 0,                       XF86XK_AudioNext,        spawn, SHCMD("playerctl next") },
	{ 0,                       XF86XK_AudioPlay,        spawn, SHCMD("playerctl play-pause") },
	{ 0,                       XF86XK_AudioPrev,        spawn, SHCMD("playerctl previous") },

	{ MODKEY,                       XK_F11,    spawn,          SHCMD("/home/jw/.scripts/powermenu.sh") },
        { MODKEY,                       XK_F12,    spawn,          SHCMD("/home/jw/.scripts/touchpad.sh") },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = rofirun } },
	{ MODKEY,                       XK_d,      spawn,          {.v = rofidrun } },
	{ MODKEY|ShiftMask,             XK_F1,     spawn,          SHCMD("spotify") },
	{ MODKEY|ShiftMask,             XK_F11,    spawn,          SHCMD("pkill picom & sleep 1 && picom &") },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          SHCMD("firefox") },
	{ MODKEY|ShiftMask,             XK_j,      spawn,          SHCMD("joplin-desktop") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("pcmanfm") },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          SHCMD("st -e vim") },
      //{ MODKEY|ShiftMask,             XK_F11,    spawn,          SHCMD("flameshot screen -p ~/Pictures/Screenshots/") },

	// { MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	// { MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	// { MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	// { MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	// { MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	// { MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	// { MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	// { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	// { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	// { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },  
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

