
Private Declare Function CreateToolhelp32Snapshot Lib "kernel32" (ByVal dwFlags As Long, ByVal th32ProcessID As Long) As Long
Private Declare Function Process32First Lib "kernel32" (ByVal hSnapshot As Long, lppe As PROCESSENTRY32) As Long
Private Declare Function Process32Next Lib "kernel32" (ByVal hSnapshot As Long, lppe As PROCESSENTRY32) As Long
Private Type PROCESSENTRY32
        dwSize   As Long
        cntUsage   As Long
        th32ProcessID   As Long
        th32DefaultHeapID   As Long
        th32ModuleID   As Long
        cntThreads   As Long
        th32ParentProcessID   As Long
        pcPriClassBase   As Long
        dwFlags   As Long
        szExeFile   As String * 1024
End Type

Const TH32CS_SNAPHEAPLIST = &H1
Const TH32CS_SNAPPROCESS = &H2
Const TH32CS_SNAPTHREAD = &H4
Const TH32CS_SNAPMODULE = &H8
Const TH32CS_SNAPALL = (TH32CS_SNAPHEAPLIST Or TH32CS_SNAPPROCESS Or TH32CS_SNAPTHREAD Or TH32CS_SNAPMODULE)
Const TH32CS_INHERIT = &H80000000

Dim pid    As Long
Dim pname    As String
Dim a As String

Private Sub Command1_Click()
    a = Trim(LCase(Text1))
    Dim my    As PROCESSENTRY32
    Dim l    As Long
    Dim l1    As Long
    Dim flag    As Boolean
    Dim mName    As String
    Dim i    As Integer
    
    l = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)
    
    If l Then
        my.dwSize = 1060
    End If
        
    If (Process32First(l, my)) Then      '遍历第一个进程
        Do
            i = InStr(1, my.szExeFile, Chr(0))  '返回chr(0)在各个进程中出现的位置
            mName = LCase(Left(my.szExeFile, i - 1)) '返回小写的（返回i-1的前n个字符，即正确的名称）
               
            If mName = a Then
                pid = my.th32ProcessID
                Text1 = Text1 & "的pid是 " & "---" & pid
            End If
        Loop Until (Process32Next(l, my) < 1)
    End If
End Sub


