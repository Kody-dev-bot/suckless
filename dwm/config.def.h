/* 参见 LICENSE 文件了解版权和许可详情。 */

/* 外观 */
static const unsigned int borderpx  = 1;        /* 窗口边框像素 */
static const unsigned int gappx     = 8;        /* 窗口之间的间隙 */
static const unsigned int snap      = 32;       /* 吸附像素 */
static const unsigned int systraypinning = 0;   /* 0: 系统托盘随选中的显示器移动，>0: 将系统托盘固定到 X 号显示器 */
static const unsigned int systrayonleft = 0;    /* 0: 系统托盘在右下角，>0: 系统托盘在状态文本左侧 */
static const unsigned int systrayspacing = 2;   /* 系统托盘间距 */
static const int systraypinningfailfirst = 1;   /* 1: 若固定失败，在第一个显示器显示系统托盘，0: 在最后一个显示器显示系统托盘 */
static const int showsystray        = 1;        /* 0 表示不显示系统托盘 */
static const int showbar            = 1;        /* 0 表示不显示状态栏 */
static const int topbar             = 1;        /* 0 表示状态栏在底部 */
static const int user_bh            = 2;        /* 2 是状态栏字体周围的默认间距 */
static const Bool viewontag         = True;     /* 切换标签时切换视图 */
static const char *fonts[]          = { "Hack Nerd Font Mono:size=18" };
static const char col_bg[]       = "#282a36";
static const char col_fg[]       = "#f8f8f2";
static const char col_sel_fg[]   = "#f8f8f2";
static const char col_sel_bg[]   = "#bd93f9";
static const char col_hid_fg[]   = "#6272a4";
static const char col_hid_bg[]   = "#21222c";
static const char col_urg_fg[]   = "#ff5555";
static const char *colors[][3]      = {
    /*               前景色      背景色      边框色   */
    [SchemeNorm] = { col_fg, col_bg, col_hid_fg },
    [SchemeSel]  = { col_sel_fg, col_sel_bg, col_sel_bg },
    [SchemeHid]  = { col_hid_fg, col_hid_bg, col_hid_fg },
    [SchemeStatus]  = { col_fg, col_bg,  "#000000"  }, // 右侧状态栏 {文本,背景,未使用但不能为空}
    [SchemeTagsSel]  = { col_sel_fg, col_sel_bg,  "#000000"  }, // 左侧标签栏选中状态 {文本,背景,未使用但不能为空}
    [SchemeTagsNorm]  = { col_fg, col_bg,  "#000000"  }, // 左侧标签栏未选中状态 {文本,背景,未使用但不能为空}
    [SchemeInfoSel]  = { col_sel_fg, col_sel_bg,  "#000000"  }, // 中间信息栏选中状态 {文本,背景,未使用但不能为空}
    [SchemeInfoNorm]  = { col_fg, col_bg,  "#000000"  }, // 中间信息栏未选中状态 {文本,背景,未使用但不能为空}
};

static const char *const autostart[] = {
  "fcitx5", NULL,
  "picom", NULL,
  "/usr/local/bin/slstatus", NULL,
  "/usr/local/bin/wallpaper", "loop", NULL,
};

/* 标签 */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = 实例名, 类名
	 *	WM_NAME(STRING) = 标题
	 */
	/* 类名       实例名      标题          标签掩码      是否浮动      显示器 */
	{ "Yad",      NULL,       "dwm-shortcuts", 0,            1,           -1 },
};

/* 布局 */
static const float mfact     = 0.55; /* 主区域大小比例 [0.05..0.95] */
static const int nmaster     = 1;    /* 主区域中的客户端数量 */
static const int resizehints = 1;    /* 1 表示在平铺调整大小时遵循大小提示 */
static const int lockfullscreen = 1; /* 1 将强制焦点在全屏窗口上 */
static const int refreshrate = 120;  /* 客户端移动/调整大小时的刷新率（每秒） */

static const Layout layouts[] = {
	/* 符号       排列函数 */
	{ "[]=",      tile },    /* 第一个条目是默认值 */
	{ "><>",      NULL },    /* 无布局函数表示浮动行为 */
	{ "[M]",      monocle },
};

/* 按键定义 */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* 以 dwm-5.0 之前的方式生成 shell 命令的辅助工具 */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* 命令 */
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "st", NULL };

static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static const char *screenshotcmd[] = { "flameshot", "gui", NULL };

static const char *setupwallpaper[] = { "wallpaper", "setup", NULL };


static const Key keys[] = {
	/* 修饰键                       按键         函数           参数 */
  { MODKEY,                     XK_p,                    spawn,            {.v = dmenucmd } },
  { MODKEY,                     XK_Return,               spawn,            {.v = termcmd } },
  { MODKEY,                     XK_a,                    spawn,            {.v = screenshotcmd} },
  { MODKEY,                     XK_r,                    spawn,            {.v = setupwallpaper} },
  { MODKEY,                     XK_apostrophe,           togglescratch,    {.v = scratchpadcmd } },
  { MODKEY,                     XK_j,                    focusstackvis,    {.i = +1 } },
  { MODKEY,                     XK_k,                    focusstackvis,    {.i = -1 } },
  { MODKEY,                     XK_i,                    incnmaster,       {.i = +1 } },
  { MODKEY,                     XK_d,                    incnmaster,       {.i = -1 } },
  { MODKEY,                     XK_t,                    setlayout,        {.v = &layouts[0]} },
  { MODKEY,                     XK_f,                    setlayout,        {.v = &layouts[1]} },
  { MODKEY,                     XK_m,                    setlayout,        {.v = &layouts[2]} },
  { MODKEY,                     XK_0,                    view,             {.ui = ~0 } },
  { MODKEY,                     XK_comma,                focusmon,         {.i = -1 } },
  { MODKEY,                     XK_period,               focusmon,         {.i = +1 } },
  { MODKEY,                     XK_minus,                setgaps,          {.i = -1 } },
  { MODKEY,                     XK_equal,                setgaps,          {.i = +1 } },
  { MODKEY,                     XK_Tab,                  view,             {0} },
  { MODKEY,                     XK_b,                    togglebar,        {0} },
  { MODKEY,                     XK_s,                    show,             {0} },
  { MODKEY,                     XK_h,                    hide,             {0} },
  { MODKEY,                     XK_Tab,                  view,             {0} },
  { MODKEY,                     XK_space,                setlayout,        {0} },

  { MODKEY|ShiftMask,           XK_0,                    tag,              {.ui = ~0 } },
  { MODKEY|ShiftMask,           XK_comma,                tagmon,           {.i = -1 } },
  { MODKEY|ShiftMask,           XK_period,               tagmon,           {.i = +1 } },
  { MODKEY|ShiftMask,           XK_equal,                setgaps,          {.i = 0  } },
  { MODKEY|ShiftMask,           XK_j,                    focusstackhid,    {.i = +1 } },
  { MODKEY|ShiftMask,           XK_k,                    focusstackhid,    {.i = -1 } },
  { MODKEY|ShiftMask,           XK_h,                    setmfact,         {.f = -0.05} },
  { MODKEY|ShiftMask,           XK_l,                    setmfact,         {.f = +0.05} },
  { MODKEY|ShiftMask,           XK_Return,               zoom,             {0} },
  { MODKEY|ShiftMask,           XK_q,                    killclient,       {0} },
  { MODKEY|ShiftMask,           XK_space,                togglefloating,   {0} },
  { MODKEY|ShiftMask,           XK_c,                    quit,             {0} },
  { MODKEY|ShiftMask,           XK_f,                    fullscreen,       {0} },
  { MODKEY|ShiftMask,           XK_s,                    showall,          {0} },


  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
  TAGKEYS(                        XK_6,                      5)
  TAGKEYS(                        XK_7,                      6)
  TAGKEYS(                        XK_8,                      7)
  TAGKEYS(                        XK_9,                      8)
};

/* 按钮定义 */
/* 点击可以是 ClkTagBar、ClkLtSymbol、ClkStatusText、ClkWinTitle、ClkClientWin 或 ClkRootWin */
static const Button buttons[] = {
	/* 点击区域               事件掩码        按钮          函数           参数 */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
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
