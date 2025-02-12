#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL InitWindowsClass(HINSTANCE hInstance);

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    MSG Message;
    if (!InitWindowsClass(hInstance)) return FALSE;
    if (!InitWindows(hInstance, nCmdShow)) return FALSE;
    while (GetMessage(&Message, 0, 0, 0)) {  // 消息循环
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}

BOOL InitWindowsClass(HINSTANCE hInstance) {  // 初始化窗口类
    WNDCLASS wndclass;                        // 窗口类
    TCHAR lpszClassName[] = L"My_Drawing";
    TCHAR lpszTitle[] = L"2021329600006_陈昊天_Win32Application_3_1";
    wndclass.style = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;  // 应用程序实例句柄
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = lpszClassName;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    return RegisterClass(&wndclass);
}
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow) {  // 初始化窗口
    HWND hwnd;
    TCHAR lpszClassName[] = L"My_Drawing";
    TCHAR lpszTitle[] = L"2021329600006_陈昊天_Win32Application_3_1";
    hwnd =
        CreateWindow(lpszClassName, lpszTitle,  // 创建窗口
                     WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                     CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);  // 显示窗口
    UpdateWindow(hwnd);          // 刷新窗口
    return TRUE;
}

// 消息处理函数
static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
                                LPARAM lParam) {
    static long nXChar, nYChar;
    HDC hDC;  // 定义指向设备上下文的句柄
    TEXTMETRIC tm;
    PAINTSTRUCT PtStr;  // 定义指向包含绘图信息的结构体变量
    LPCWSTR textbuf[] = {L"This is the First line"};
    static int X, Y, nChar;
    LPCWSTR lpsz_1;
    switch (iMessage) {                  // 处理消息
        case WM_CREATE:                  // 处理窗口创建消息
            hDC = GetDC(hWnd);           // 获取当前设备表句柄
            GetTextMetrics(hDC, &tm);    // 获取字体信息
            nXChar = tm.tmAveCharWidth;  // 获取字符宽度
            nYChar = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC(hWnd, hDC);  // 释放当前设备句柄
            return 0;
        case WM_PAINT:                       // 处理重画消息
            hDC = BeginPaint(hWnd, &PtStr);  // 开始绘画
            // for (int x = 0; x < 6; x++)    	//输出文本
            //     TextOut(hDC, nXChar, nYChar * (1 + x), textbuf[x],
            //     lstrlen(textbuf[x]));
            lpsz_1 = L"abcdefghijklmnopqrstuvwxyz";
            nChar = 26;
            Y = tm.tmExternalLeading + 10;  // 设置输出字符的Y坐标
            for (int i = 0; i < nChar; i++) {
                SetTextColor(hDC, RGB(0, 0, 0));  // 设置字体的颜色为黑色
                X = X + tm.tmAveCharWidth * 2;  // 设置输出字符的X坐标
                TextOut(hDC, X, Y, &lpsz_1[i],
                        1);  // 输出从第0个到第nChar-1个字符
            }

            EndPaint(hWnd, &PtStr);
            return 0;
        case WM_DESTROY:  // 结束应用程序
            PostQuitMessage(0);
            return 0;
        default:  // 其他消息处理程序
            return (DefWindowProc(hWnd, iMessage, wParam, lParam));
    }
}