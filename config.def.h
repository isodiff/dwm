/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 12;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Ubuntu Mono:size=14" };
static const char dmenufont[]       = "Ubuntu Mono:size=12";
static const char col_gray1[]       = "#1E1E2E";
static const char col_gray2[]       = "#1E1E2E";
static const char col_gray3[]       = "#D9E0EE";
static const char col_gray4[]       = "#D9E0EE";
static const char col_cyan[]        = "#F28FAD";
static const char *colors[][3]      = {
	/*                       fg          bg       border   */
	[SchemeNorm]     =  { col_gray3,  col_gray1, col_gray2  },
	[SchemeSel]      =  { col_gray4,  col_gray2, col_gray1  },
	[SchemeStatus]   =  { col_gray3,  col_gray1, "#000000"  },
	[SchemeTagsSel]  =  { col_gray4,  col_gray2, "#000000"  },
	[SchemeTagsNorm] =  { col_gray3,  col_gray1, "#000000"  },
	[SchemeInfoSel]  =  { col_gray4,  col_gray1, "#000000"  },
	[SchemeInfoNorm] =  { col_gray3,  col_gray1, "#000000"  },
};

/* tagging */
static const char *tags[] = { " 󰞷 ", " 󰣩 ", " 󰺿 ", " 󰅩 ", " 󰺶 " };
static const char *alttags[] = { " 󰆍 ", " 󰖟 ", " 󰠮 ", " 󰘦 ", " 󰺵 " };

static const unsigned int ulinepad     = 7;    /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke  = 2;    /* thickness / height of the underline */
static const unsigned int ulinevoffset = 0;    /* how far above the bottom of the bar the line should appear */
static const int ulineall              = 0;    /* 1 to show underline on all tags, 0 for just the active ones */

static const char *tagsel[][2] = {
	{ "#000000", "#ABE9B3" },
	{ "#000000", "#96CDFB" },
	{ "#000000", "#FAE3B0" },
	{ "#000000", "#DDB6F2" },
	{ "#000000", "#F28FAD" },
	{ "#000000", "#B5E8E0" },
	{ "#000000", "#9400d3" },
	{ "#000000", "#ffffff" },
	{ "#ffffff", "#000000" },
};


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	         instance    title                   tags mask     isfloating   monitor */
	{ "Firefox",             NULL,       NULL,       	           1 << 1,       0,           -1 },
	{ "kitty",               NULL,       "Hey, Hi, Hello",       1 << 0,       1,           -1 },
	{ "kitty",               NULL,       "Ranger",               NULL,         1,           -1 },
	{ "Ungoogled-chromium",  NULL,       NULL,                   1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " 󰍲 ",      tile },    /* first entry is default */
	{ " 󰼁 ",      NULL },    /* no layout function means floating behavior */
	{ " 󰐃 ",      monocle },
};


/* Volume controls */
#include <X11/XF86keysym.h>
static const char *upvol[]   = { "pamixer", "-i",   "5",     NULL };
static const char *downvol[] = { "pamixer", "-d",   "5",     NULL };
static const char *mutevol[] = { "pamixer", "-t",   NULL          };


/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *spwnrngr[] = { "kitty", "-T", "Ranger", "ranger", NULL };
static const char *spwnrofi[] = { "rofi", "-combi-modi", "window,drun,ssh", "-show", "drun", "-icon-theme", "\"Papirus\"", "-show-icons", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = spwnrofi } },
	/*{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } }, */
	{ MODKEY,                       XK_e,      spawn,          {.v = spwnrngr } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },
	{ 0,		XF86XK_AudioLowerVolume,   spawn,          {.v = downvol } },
	{ 0,            XF86XK_AudioMute,          spawn,          {.v = mutevol } },
	{ 0,            XF86XK_AudioRaiseVolume,   spawn,          {.v = upvol   } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

