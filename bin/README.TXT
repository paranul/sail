NOTES: 
On high DPI devices need to play around with settings > Properties of .exe  compatibility > Change DPI settings
otherwise the resolution is weird


https://docs.microsoft.com/en-us/windows/win32/hidpi/setting-the-default-dpi-awareness-for-a-process
https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setprocessdpiawarenesscontext
BOOL SetProcessDpiAwarenessContext(
  [in] DPI_AWARENESS_CONTEXT value
);




NOTE::::QuickEdit Mode (Console CMD highlighting feature freezes the application)
--A Quick fix is to right click on the command window do exit highlighting mode

https://stackoverflow.com/questions/55497407/disable-quick-edit-mode-for-console-from-c