크기 Rect
TitleRect와 GraphRect로 만들고 

브러시
화면 지우기용 브러시

폰트는 안티알라이싱 모드를 넣어준다.
폰트 -> 그리드 지표용, 타이틀 출력용

펜은 BackGround 색보다 밝게 한다. 
그리드(펜)는 BackGround는 펜보다 덜밝게 만든다.
펜 -> 그래프 라인 펜, 그리드 라인 펜


더블 버퍼링은 지난번에 했던대로 하면된다.
SetBkMode(HDC 값, TRANSPARENT);  -> Textout을 하면 기본적으로 백그라운드가 하얀색 이를 투명색으로

파괴자
폰트 메모리 윈도우 파괴하면된다


// 알람



1. WindowRect -> TitleRect, GraphRect 설정(크기)
2. TitleRect에 TextOut함(Font 설정후에 출력 SetBkMode(HDC 값, TRANSPARENT) 이용해서)
2-1. TitleRect에 색 지정 밝은 회색 정도


3. Graph타입에 맞게 그린다.  ( 최소 최대값 설정 ) -> MemDC에 그린다. (in WndProc Function wm_paint)
3-1. 비율 문제  Width 는 Window의 Rect 의 최하단(bottom) 이 0, 최대 값은 top - TitleRect의 bottom
 -- 최대값은 Peek하면서 최대값으로 지정  
3-2. 그리드 라인 분배(비율에 맞게 수치 표시 및 선 그리기) 4등분(정수 타입)
3-3. 위의 조건에 맞게 펜으로 그린다.


OutputDebugString(WCHAR str) 출력창에 출력해준다. 문자열만 된다


// UM_ALERT 는 WM_USER + 1 커스텀으로 만든 메세지

SendMessage(_hWndParent, UM_ALERT, 0, 0);

일정시간은 무시해야된다. 2,3초 정도