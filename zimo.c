char xdy[]={
/*--  线  --*/
0x10,0x10,0x10,0xD0,0xFF,0x90,0x10,0x00,0xFE,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,
0x08,0x04,0x03,0x00,0xFF,0x00,0x03,0x00,0xFF,0x42,0x42,0x42,0x42,0xFF,0x00,0x00,
/*--  电  --*/
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,
/*--  压  --*/
0x00,0x00,0xFE,0x02,0x82,0x82,0x82,0x82,0xFA,0x82,0x82,0x82,0x82,0x82,0x02,0x00,
0x80,0x60,0x1F,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x44,0x58,0x40,0x40,0x00,
/*--  :  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
char he[]={
/*--  和  --*/
0x20,0x24,0x24,0xA4,0xFE,0x23,0x22,0x20,0x00,0xF8,0x08,0x08,0x08,0xF8,0x00,0x00,
0x10,0x08,0x06,0x01,0xFF,0x01,0x06,0x00,0x00,0x3F,0x10,0x10,0x10,0x3F,0x00,0x00
//0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
//0x10,0x30,0x10,0x1F,0x08,0x88,0x48,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,
//0x04,0x24,0x24,0x25,0x7F,0xC4,0x44,0x04,0x00,0x1F,0x10,0x10,0x10,0x1F,0x00,0x00,
//0x08,0x10,0x60,0x80,0xFF,0x80,0x60,0x00,0x00,0xFC,0x08,0x08,0x08,0xFC,0x00,0x00,
};
//功率参数
char glcs[]={
/*--  功  --*/
0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
0x10,0x30,0x10,0x1F,0x08,0x88,0x48,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,
/*--  率  --*/
0x00,0x14,0xA4,0x44,0x24,0x34,0xAD,0x66,0x24,0x94,0x04,0x44,0xA4,0x14,0x00,0x00,
0x08,0x09,0x08,0x08,0x09,0x09,0x09,0xFD,0x09,0x09,0x0B,0x08,0x08,0x09,0x08,0x00,
/*--  参  --*/
0x00,0x20,0x20,0xA8,0x6C,0x2A,0x39,0x28,0xA8,0x2A,0x6C,0xA8,0x20,0x20,0x00,0x00,
0x02,0x82,0x81,0x90,0x92,0x4A,0x49,0x45,0x24,0x22,0x10,0x08,0x01,0x02,0x02,0x00,
/*--  数  --*/
0x90,0x52,0x34,0x10,0xFF,0x10,0x34,0x52,0x80,0x70,0x8F,0x08,0x08,0xF8,0x08,0x00,
0x82,0x9A,0x56,0x63,0x22,0x52,0x8E,0x00,0x80,0x40,0x33,0x0C,0x33,0x40,0x80,0x00
};
char pc[]={
/*--  偏  --*/
0x80,0x60,0xF8,0x07,0x00,0xFC,0x24,0x24,0x25,0x26,0x24,0x24,0x24,0x3C,0x00,0x00,
0x00,0x00,0xFF,0x40,0x3C,0x03,0xFF,0x09,0x7F,0x09,0x7F,0x09,0x89,0xFF,0x00,0x00,
/*--  差  --*/
0x00,0x04,0x24,0x24,0x25,0x26,0xE4,0x3C,0x24,0x26,0x25,0x24,0x24,0x04,0x00,0x00,
0x41,0x21,0x11,0x89,0x85,0x8B,0x89,0x89,0xF9,0x89,0x89,0x89,0x89,0x81,0x01,0x00,
};
char ppt[]={
/*--  频  --*/
0x40,0x7C,0x40,0x7F,0x48,0x48,0x40,0xF2,0x12,0x1A,0xD6,0x12,0x12,0xF2,0x02,0x00,
0x90,0x8E,0x40,0x4F,0x20,0x1E,0x80,0x4F,0x20,0x18,0x07,0x10,0x20,0x4F,0x80,0x00,
/*--  谱  --*/
0x40,0x42,0xCC,0x00,0x40,0x54,0x65,0x46,0x7C,0x44,0x7C,0x46,0x65,0x54,0x40,0x00,
0x00,0x00,0x7F,0x20,0x10,0x00,0xFF,0x49,0x49,0x49,0x49,0x49,0xFF,0x00,0x00,0x00,
/*--  图  --*/
0x00,0xFE,0x02,0x42,0x22,0x32,0x5E,0x92,0x52,0x32,0x12,0x02,0x02,0xFE,0x00,0x00,
0x00,0xFF,0x42,0x42,0x42,0x51,0x55,0x64,0x69,0x41,0x42,0x42,0x42,0xFF,0x00,0x00
};
char xdl[]={
/*--  线  --*/
0x10,0x10,0x10,0xD0,0xFF,0x90,0x10,0x00,0xFE,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,
0x08,0x04,0x03,0x00,0xFF,0x00,0x03,0x00,0xFF,0x42,0x42,0x42,0x42,0xFF,0x00,0x00,
/*--  电  --*/
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,
/*--  流  --*/
0x10,0x60,0x02,0x8C,0x00,0x44,0x64,0x54,0x4D,0x46,0x44,0x54,0x64,0xC4,0x04,0x00,
0x04,0x04,0x7E,0x01,0x80,0x40,0x3E,0x00,0x00,0xFE,0x00,0x00,0x7E,0x80,0xE0,0x00,
/*--  :  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
char yggl[]={
/*--  有  --*/
0x04,0x04,0x04,0x84,0xE4,0x3C,0x27,0x24,0x24,0x24,0x24,0xE4,0x04,0x04,0x04,0x00,
0x04,0x02,0x01,0x00,0xFF,0x09,0x09,0x09,0x09,0x49,0x89,0x7F,0x00,0x00,0x00,0x00,
/*--  功  --*/
0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
0x10,0x30,0x10,0x1F,0x08,0x88,0x48,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,
/*--  功  --*/
0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
0x10,0x30,0x10,0x1F,0x08,0x88,0x48,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,
/*--  率  --*/
0x00,0x14,0xA4,0x44,0x24,0x34,0xAD,0x66,0x24,0x94,0x04,0x44,0xA4,0x14,0x00,0x00,
0x08,0x09,0x08,0x08,0x09,0x09,0x09,0xFD,0x09,0x09,0x0B,0x08,0x08,0x09,0x08,0x00,
};
char wggl[]={
/*--  无 --*/
0x00,0x40,0x42,0x42,0x42,0xC2,0x7E,0x42,0xC2,0x42,0x42,0x42,0x40,0x40,0x00,0x00,
0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x00,0x3F,0x40,0x40,0x40,0x40,0x70,0x00,0x00,
/*--  功  --*/
0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
0x10,0x30,0x10,0x1F,0x08,0x88,0x48,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,
/*--  功  --*/
0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
0x10,0x30,0x10,0x1F,0x08,0x88,0x48,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,
/*--  率  --*/
0x00,0x14,0xA4,0x44,0x24,0x34,0xAD,0x66,0x24,0x94,0x04,0x44,0xA4,0x14,0x00,0x00,
0x08,0x09,0x08,0x08,0x09,0x09,0x09,0xFD,0x09,0x09,0x0B,0x08,0x08,0x09,0x08,0x00,
};
char szgl[]={
/*--  视  --*/
0x08,0x08,0x89,0xEE,0x98,0x00,0x00,0xFE,0x02,0x02,0xF2,0x02,0x02,0xFE,0x00,0x00,
0x02,0x01,0x00,0xFF,0x00,0x83,0x40,0x23,0x18,0x06,0x01,0x7E,0x80,0x83,0xE0,0x00,
/*--  在  --*/
0x08,0x08,0x88,0xC8,0x38,0x0C,0x0B,0x08,0x08,0xE8,0x08,0x08,0x08,0x08,0x08,0x00,
0x02,0x01,0x00,0xFF,0x40,0x41,0x41,0x41,0x41,0x7F,0x41,0x41,0x41,0x41,0x40,0x00,
/*--  功  --*/
0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
0x10,0x30,0x10,0x1F,0x08,0x88,0x48,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,
/*--  率  --*/
0x00,0x14,0xA4,0x44,0x24,0x34,0xAD,0x66,0x24,0x94,0x04,0x44,0xA4,0x14,0x00,0x00,
0x08,0x09,0x08,0x08,0x09,0x09,0x09,0xFD,0x09,0x09,0x0B,0x08,0x08,0x09,0x08,0x00,
};
char bphd[]={
/*--  不  --*/
0x00,0x02,0x02,0x02,0x02,0x82,0x42,0xF2,0x0E,0x42,0x82,0x02,0x02,0x02,0x00,0x00,
0x10,0x08,0x04,0x02,0x01,0x00,0x00,0xFF,0x00,0x00,0x00,0x01,0x02,0x0C,0x00,0x00,
/*--  平  --*/
0x00,0x02,0x02,0x12,0x62,0x02,0x02,0xFE,0x02,0x02,0x42,0x32,0x02,0x02,0x00,0x00,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,
/*--  衡  --*/
0x10,0x88,0xC4,0x23,0x08,0xF4,0x93,0xF2,0x9A,0xF6,0x00,0x40,0x44,0xC4,0x44,0x00,
0x01,0x00,0xFF,0x00,0x10,0x97,0x54,0x3F,0x54,0x97,0x10,0x40,0x80,0x7F,0x00,0x00,
/*--  度  --*/
0x00,0x00,0xFC,0x24,0x24,0x24,0xFC,0x25,0x26,0x24,0xFC,0x24,0x24,0x24,0x04,0x00,
0x40,0x30,0x8F,0x80,0x84,0x4C,0x55,0x25,0x25,0x25,0x55,0x4C,0x80,0x80,0x80,0x00,
/*--  :  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
char glys[]={
/*--  功  --*/
0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
0x10,0x30,0x10,0x1F,0x08,0x88,0x48,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,
/*--  率  --*/
0x00,0x14,0xA4,0x44,0x24,0x34,0xAD,0x66,0x24,0x94,0x04,0x44,0xA4,0x14,0x00,0x00,
0x08,0x09,0x08,0x08,0x09,0x09,0x09,0xFD,0x09,0x09,0x0B,0x08,0x08,0x09,0x08,0x00,
/*--  因  --*/
0x00,0xFE,0x02,0x42,0x42,0x42,0x42,0xFA,0x42,0x42,0x42,0x42,0x02,0xFE,0x00,0x00,
0x00,0xFF,0x40,0x50,0x48,0x44,0x43,0x40,0x41,0x42,0x44,0x58,0x40,0xFF,0x00,0x00,
/*--  数 --*/
0x90,0x52,0x34,0x10,0xFF,0x10,0x34,0x52,0x80,0x70,0x8F,0x08,0x08,0xF8,0x08,0x00,
0x82,0x9A,0x56,0x63,0x22,0x52,0x8E,0x00,0x80,0x40,0x33,0x0C,0x33,0x40,0x80,0x00,
};
char dyspc[]={
/*--  文字:  电  --*/
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,
/*--  文字:  压  --*/
0x00,0x00,0xFE,0x02,0x82,0x82,0x82,0x82,0xFA,0x82,0x82,0x82,0x82,0x82,0x02,0x00,
0x80,0x60,0x1F,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x44,0x58,0x40,0x40,0x00,
/*--  文字:  上  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x00,
0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,
/*--  文字:  偏  --*/
0x80,0x60,0xF8,0x07,0x00,0xFC,0x24,0x24,0x25,0x26,0x24,0x24,0x24,0x3C,0x00,0x00,
0x00,0x00,0xFF,0x40,0x3C,0x03,0xFF,0x09,0x7F,0x09,0x7F,0x09,0x89,0xFF,0x00,0x00,
/*--  文字:  差  --*/
0x00,0x04,0x24,0x24,0x25,0x26,0xE4,0x3C,0x24,0x26,0x25,0x24,0x24,0x04,0x00,0x00,
0x41,0x21,0x11,0x89,0x85,0x8B,0x89,0x89,0xF9,0x89,0x89,0x89,0x89,0x81,0x01,0x00,
};
char dyxpc[]={
/*--  文字:  电  --*/
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,
/*--  文字:  压  --*/
0x00,0x00,0xFE,0x02,0x82,0x82,0x82,0x82,0xFA,0x82,0x82,0x82,0x82,0x82,0x02,0x00,
0x80,0x60,0x1F,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x44,0x58,0x40,0x40,0x00,
/*--  文字:  下  --*/
0x02,0x02,0x02,0x02,0x02,0x02,0xFE,0x02,0x02,0x42,0x82,0x02,0x02,0x02,0x02,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x01,0x06,0x00,0x00,0x00,
/*--  文字:  偏  --*/
0x80,0x60,0xF8,0x07,0x00,0xFC,0x24,0x24,0x25,0x26,0x24,0x24,0x24,0x3C,0x00,0x00,
0x00,0x00,0xFF,0x40,0x3C,0x03,0xFF,0x09,0x7F,0x09,0x7F,0x09,0x89,0xFF,0x00,0x00,
/*--  文字:  差  --*/
0x00,0x04,0x24,0x24,0x25,0x26,0xE4,0x3C,0x24,0x26,0x25,0x24,0x24,0x04,0x00,0x00,
0x41,0x21,0x11,0x89,0x85,0x8B,0x89,0x89,0xF9,0x89,0x89,0x89,0x89,0x81,0x01,0x00,
};
char pl[]={
/*--  文字:  频  --*/
0x40,0x7C,0x40,0x7F,0x48,0x48,0x40,0xF2,0x12,0x1A,0xD6,0x12,0x12,0xF2,0x02,0x00,
0x90,0x8E,0x40,0x4F,0x20,0x1E,0x80,0x4F,0x20,0x18,0x07,0x10,0x20,0x4F,0x80,0x00,
/*--  文字:  率  --*/
0x00,0x14,0xA4,0x44,0x24,0x34,0xAD,0x66,0x24,0x94,0x04,0x44,0xA4,0x14,0x00,0x00,
0x08,0x09,0x08,0x08,0x09,0x09,0x09,0xFD,0x09,0x09,0x0B,0x08,0x08,0x09,0x08,0x00,
/*--  文字:  ：  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
char f[]={
/*--  文字:  乏  --*/
0x00,0x84,0x84,0x84,0x84,0x84,0x94,0xE2,0x82,0x82,0x82,0x83,0x82,0x00,0x00,0x00,
0x40,0x20,0x10,0x10,0x28,0x48,0x44,0x44,0x42,0x42,0x41,0x41,0x40,0x40,0x40,0x00,
};
char w[]={
/*--  文字:  瓦  --*/
0x02,0x02,0x02,0x02,0xC2,0x3E,0xA2,0x22,0x22,0x22,0xE2,0x02,0x02,0x02,0x02,0x00,
0x00,0x00,0x00,0x78,0x27,0x20,0x10,0x13,0x00,0x00,0x3F,0x40,0x40,0x40,0x78,0x00,
};
char dyzdsj[]={
/*--  文字:  电  --*/
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,
/*--  文字:  压  --*/
0x00,0x00,0xFE,0x02,0x82,0x82,0x82,0x82,0xFA,0x82,0x82,0x82,0x82,0x82,0x02,0x00,
0x80,0x60,0x1F,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x44,0x58,0x40,0x40,0x00,
/*--  文字:  中  --*/
0x00,0x00,0xF0,0x10,0x10,0x10,0x10,0xFF,0x10,0x10,0x10,0x10,0xF0,0x00,0x00,0x00,
0x00,0x00,0x0F,0x04,0x04,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x0F,0x00,0x00,0x00,
/*--  文字:  断  --*/
0x00,0xFC,0x20,0x24,0xA8,0xFF,0xA8,0x24,0x00,0xFC,0x44,0x44,0xC4,0x42,0x40,0x00,
0x00,0x3F,0x22,0x21,0x20,0x2F,0x20,0xA3,0x60,0x1F,0x00,0x00,0xFF,0x00,0x00,0x00,
/*--  文字:  事  --*/
0x04,0x04,0x74,0x54,0x54,0x54,0x54,0xFF,0x54,0x54,0x54,0x54,0x74,0x04,0x04,0x00,
0x04,0x04,0x15,0x15,0x15,0x55,0x95,0x7F,0x15,0x15,0x15,0x15,0x1F,0x04,0x04,0x00,
/*--  文字:  件  --*/
0x00,0x80,0x60,0xF8,0x07,0x80,0x60,0x1C,0x10,0x10,0xFF,0x10,0x10,0x10,0x00,0x00,
0x01,0x00,0x00,0xFF,0x00,0x02,0x02,0x02,0x02,0x02,0xFF,0x02,0x02,0x02,0x02,0x00,
};
char dyzjsj[]={
/*--  文字:  电  --*/
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,
/*--  文字:  压  --*/
0x00,0x00,0xFE,0x02,0x82,0x82,0x82,0x82,0xFA,0x82,0x82,0x82,0x82,0x82,0x02,0x00,
0x80,0x60,0x1F,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x44,0x58,0x40,0x40,0x00,
/*--  文字:  暂  --*/
0x82,0x9A,0x96,0x93,0xFA,0x52,0x52,0x80,0x7E,0x12,0x12,0x12,0xF1,0x11,0x10,0x00,
0x00,0x01,0x00,0xFE,0x93,0x92,0x93,0x92,0x92,0x92,0x92,0xFE,0x03,0x00,0x00,0x00,
/*--  文字:  降  --*/
0x00,0xFE,0x02,0x22,0xDA,0x86,0x90,0x48,0x57,0x24,0xA4,0x54,0x4C,0x84,0x80,0x00,
0x00,0xFF,0x08,0x10,0x08,0x07,0x18,0x12,0x12,0x12,0xFF,0x12,0x12,0x12,0x10,0x00,
/*--  文字:  事  --*/
0x04,0x04,0x74,0x54,0x54,0x54,0x54,0xFF,0x54,0x54,0x54,0x54,0x74,0x04,0x04,0x00,
0x04,0x04,0x15,0x15,0x15,0x55,0x95,0x7F,0x15,0x15,0x15,0x15,0x1F,0x04,0x04,0x00,
/*--  文字:  件  --*/
0x00,0x80,0x60,0xF8,0x07,0x80,0x60,0x1C,0x10,0x10,0xFF,0x10,0x10,0x10,0x00,0x00,
0x01,0x00,0x00,0xFF,0x00,0x02,0x02,0x02,0x02,0x02,0xFF,0x02,0x02,0x02,0x02,0x00,
};
char xiang[]={
/*--  文字:  相  --*/
0x10,0x10,0x10,0xD0,0xFF,0x90,0x10,0x00,0xFE,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,
0x08,0x04,0x03,0x00,0xFF,0x00,0x03,0x00,0xFF,0x42,0x42,0x42,0x42,0xFF,0x00,0x00,
};
char dy[]={
/*--  文字:  电  --*/
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,
/*--  文字:  压  --*/
0x00,0x00,0xFE,0x02,0x82,0x82,0x82,0x82,0xFA,0x82,0x82,0x82,0x82,0x82,0x02,0x00,
0x80,0x60,0x1F,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x44,0x58,0x40,0x40,0x00,
};
char xb[]={
/*--  文字:  谐  --*/
0x40,0x40,0x42,0xCC,0x00,0x00,0x7F,0x24,0x94,0x40,0x3F,0x48,0x44,0x42,0x70,0x00,
0x00,0x00,0x00,0x7F,0x20,0x10,0xFF,0x49,0x49,0x49,0x49,0x49,0x49,0xFF,0x00,0x00,
/*--  文字:  波  --*/
0x10,0x60,0x02,0x0C,0xC0,0x00,0xF8,0x88,0x88,0x88,0xFF,0x88,0x88,0xA8,0x18,0x00,
0x04,0x04,0x7C,0x03,0x80,0x60,0x1F,0x80,0x43,0x2C,0x10,0x28,0x46,0x81,0x80,0x00,
};
char hl[]={
/*--  文字:  含  --*/
0x40,0x40,0x20,0x20,0x90,0x88,0x94,0xE3,0x84,0x88,0x90,0x20,0x20,0x40,0x40,0x00,
0x00,0x00,0x00,0xFC,0x44,0x44,0x44,0x44,0x46,0x45,0x44,0xFC,0x00,0x00,0x00,0x00,
/*--  文字:  量  --*/
0x20,0x20,0x20,0xBE,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xBE,0x20,0x20,0x20,0x00,
0x00,0x80,0x80,0xAF,0xAA,0xAA,0xAA,0xFF,0xAA,0xAA,0xAA,0xAF,0x80,0x80,0x00,0x00,
};
char dl[]={
/*--  文字:  电  --*/
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,
/*--  文字:  流  --*/
0x10,0x60,0x02,0x8C,0x00,0x44,0x64,0x54,0x4D,0x46,0x44,0x54,0x64,0xC4,0x04,0x00,
0x04,0x04,0x7E,0x01,0x80,0x40,0x3E,0x00,0x00,0xFE,0x00,0x00,0x7E,0x80,0xE0,0x00,
};