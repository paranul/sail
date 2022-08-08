NOTES: 
On high DPI devices need to play around with settings > Properties of .exe  compatibility > Change DPI settings
otherwise the resolution is weird


https://docs.microsoft.com/en-us/windows/win32/hidpi/setting-the-default-dpi-awareness-for-a-process
https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setprocessdpiawarenesscontext
BOOL SetProcessDpiAwarenessContext(
  [in] DPI_AWARENESS_CONTEXT value
);
