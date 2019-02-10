# 정리

## GetMessage, PeekMessage 차이점

> 두 함수 윈도우 메세지 큐에서 가져온다. Get은 큐에서 제거하지만 Peek Message는 제거하지 않는다.

## Handle

> 운영체제는 각 윈도우를 관리하는 구조체를 유지함. 
>
> 직접적인 프로그래밍을 방지하기 위해서, 간접적인 정수 값을 주는데 이를 핸들이라고 함.
>
> 윈도우에 그리기위해서는 먼저 윈도우 핸들을 얻어야 됨.

## Device Context

> 여러 그리기 정보(선의 굵기, 색상, 좌표계, 클리핑, 바탕화면 색 등)에 대한 구조체를 DC(Device Context)라고 함.

## Windows Message Queue

![](.\Pic1.PNG)

