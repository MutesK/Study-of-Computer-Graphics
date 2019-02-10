#pragma once
#pragma once

#define dfMAXCHILD		100

//-----------------------------------------------------
// 폰트 사이즈, 타이틀 / 그래프 지표
//-----------------------------------------------------

// 타이틀 
//-----------------------------------------------------
#define dfWindowTitle_HEIGHT 40


#define dfLINEMULTI_DATAWIDTH 200


#define UM_ALERT WM_USER + 1

#define FLUOCOLOR_YELLOW RGB(203, 255, 117)

#define DARKGRAY RGB(0x28, 0x28, 0x28)
#define BRIGHTGRAY RGB(0x46, 0x46, 0x46)
#define VBRIGHTGRAY RGB(0x78, 0x78, 0x78)
#define DRAKGREEN RGB(0, 100, 0)
#define RED RGB(0xff, 0x00, 0x00)
#define BLACK RGB(0,0,0)
#define WHITE RGB(0xff, 0xff, 0xff)


// 멀티 라인용
#define YELLOW RGB(0xe6, 0xff, 0x00)
#define GREEN RGB(0x4c, 0xff, 0x00)
#define PINK RGB(0xff, 0x00, 0xb2)
#define BLUE RGB(0x18, 0x00, 0xff)
#define NGREEN RGB(0, 128, 0)

#define COLUMN_MAX 10
#define WINDOW_NAME 200

#define GRIDFONT_HEIGHT 15
#define TITLEFONT_HEIGHT 20


/*
자식윈도우는 1 ~ 10개의 칼럼을 가진다.

- 고정 요소 -
타이틀 펜(크기)
그리드 색깔
그리드 폰트

정상작동중일때 타이틀 텍스트가 하얀색, 위험 -> 빨간색
*/