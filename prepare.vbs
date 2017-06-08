Function UserInput( myPrompt )
' This function prompts the user for some input.
' When the script runs in CSCRIPT.EXE, StdIn is used,
' otherwise the VBScript InputBox( ) function is used.
' myPrompt is the the text used to prompt the user for input.
' The function returns the input typed either on StdIn or in InputBox( ).
' Written by Rob van der Woude
' http://www.robvanderwoude.com
    ' Check if the script runs in CSCRIPT.EXE
    If UCase( Right( WScript.FullName, 12 ) ) = "\CSCRIPT.EXE" Then
        ' If so, use StdIn and StdOut
        WScript.StdOut.Write myPrompt & " "
        UserInput = WScript.StdIn.ReadLine
    Else
        ' If not, use InputBox( )
        UserInput = InputBox( myPrompt )
    End If
End Function

Function SelectFolder( myStartFolder )
' This function opens a "Select Folder" dialog and will
' return the fully qualified path of the selected folder
'
' Argument:
'     myStartFolder    [string]    the root folder where you can start browsing;
'                                  if an empty string is used, browsing starts
'                                  on the local computer
'
' Returns:
' A string containing the fully qualified path of the selected folder
'
' Written by Rob van der Woude
' http://www.robvanderwoude.com

    ' Standard housekeeping
    Dim objFolder, objItem, objShell
    
    ' Custom error handling
    On Error Resume Next
    SelectFolder = vbNull

    ' Create a dialog object
    Set objShell  = CreateObject( "Shell.Application" )
    Set objFolder = objShell.BrowseForFolder( 0, "Gdzie zapisaæ plik z projektem dla prowadz¹cego?", 0, myStartFolder )

    ' Return the path of the selected folder
    If IsObject( objfolder ) Then SelectFolder = objFolder.Self.Path

    ' Standard housekeeping
    Set objFolder = Nothing
    Set objshell  = Nothing
    On Error Goto 0
End Function

Function SelectFile( )
    ' File Browser via HTA
    ' Author:   Rudi Degrande, modifications by Denis St-Pierre and Rob van der Woude
    ' Features: Works in Windows Vista and up (Should also work in XP).
    '           Fairly fast.
    '           All native code/controls (No 3rd party DLL/ XP DLL).
    ' Caveats:  Cannot define default starting folder.
    '           Uses last folder used with MSHTA.EXE stored in Binary in [HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\ComDlg32].
    '           Dialog title says "Choose file to upload".
    ' Source:   https://social.technet.microsoft.com/Forums/scriptcenter/en-US/a3b358e8-15ae-4ba3-bca5-ec349df65ef6/windows7-vbscript-open-file-dialog-box-fakepath?forum=ITCG

    Dim objExec, strMSHTA, wshShell

    SelectFile = ""

    ' For use in HTAs as well as "plain" VBScript:
    strMSHTA = "mshta.exe ""about:" & "<" & "input type=file id=FILE>" _
             & "<" & "script>FILE.click();new ActiveXObject('Scripting.FileSystemObject')" _
             & ".GetStandardStream(1).WriteLine(FILE.value);close();resizeTo(0,0);" & "<" & "/script>"""
    ' For use in "plain" VBScript only:
    ' strMSHTA = "mshta.exe ""about:<input type=file id=FILE>" _
    '          & "<script>FILE.click();new ActiveXObject('Scripting.FileSystemObject')" _
    '          & ".GetStandardStream(1).WriteLine(FILE.value);close();resizeTo(0,0);</script>"""

    Set wshShell = CreateObject( "WScript.Shell" )
    Set objExec = wshShell.Exec( strMSHTA )

    SelectFile = objExec.StdOut.ReadLine( )

    Set objExec = Nothing
    Set wshShell = Nothing
End Function

Set objArgs = WScript.Arguments

strProjectFolder 	= objArgs(0)

strReportPath = ""
Do 
	strName = UserInput("Imiê:") 
Loop Until strName <> ""

Do 
	strSurname 	= UserInput("Nazwisko:")
Loop Until strSurname <> ""

Do 
	strGroup = UserInput("Numer grupy:")
Loop Until strGroup <> ""

WScript.Echo "Wybierz teraz plik, ktory zawiera sprawozdanie do projektu!"
strReportPath = SelectFile()
strPath = SelectFolder( "" )
If strPath = vbNull Then
    WScript.Echo "Nie wybra³eœ œcie¿ki do zapisu pliku"
	WScript.Quit
Else
    
	strZipPath = strPath & "\" &strGroup & "_" & strSurname & "_" & strName & ".zip"

	Dim objCmd 
	Set objCmd = CreateObject("Wscript.Shell") 
	objCmd.Run("cmd.exe /C copy """ & strReportPath & """ """ & strProjectFolder & """")
	Wscript.Sleep 2000
	
	CreateObject("Scripting.FileSystemObject").CreateTextFile(strZipPath, True).Write "PK" & Chr(5) & Chr(6) & String(18, vbNullChar)

	Set objShell = CreateObject("Shell.Application")

	Set source = objShell.NameSpace(strProjectFolder).Items

	objShell.NameSpace(strZipPath).CopyHere(source)	
	Wscript.Sleep 2000

	Dim Fso
	Set Fso = WScript.CreateObject("Scripting.FileSystemObject")
	Fso.MoveFile strPath & "\" &strGroup & "_" & strSurname & "_" & strName & ".zip", strPath & "\" &strGroup & "_" & strSurname & "_" & strName & ".lip"

	WScript.Echo "Zapisano do: " & strPath & "\" &strGroup & "_" & strSurname & "_" & strName & ".lip"
	WScript.Quit
End If


