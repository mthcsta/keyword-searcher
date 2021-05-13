:start
@echo off

set PROGRAM="bin/Debug/Buscador de Palavras Chave.exe"
set INPUT="test/input/100.txt"
set QUERY="test/query/10.txt"
set tempo=%time: =%
set default=%date:/=-%-%tempo::=-%
set OUTPUT="test/output/%default:,=%.txt"
set TREE="CMP"
set TIMES=1



CLS 
@echo --------------------------------------------------------------------------------
@echo arquivos disponiveis para leitura:
dir /b "test/input/"
@echo. 

set /P inputfilename="Digite o arquivo para leitura: "
if [%inputfilename%] NEQ [] set INPUT="test/input/%inputfilename%"

CLS
@echo arquivo para leitura: %INPUT%
@echo --------------------------------------------------------------------------------
@echo arquivos disponiveis para consulta:
dir /b "test/query/"
@echo. 

set /P queryfilename="Digite o arquivo para consulta: "
if [%queryfilename%] NEQ [] set QUERY="test/query/%queryfilename%"

CLS
@echo arquivo para leitura: %INPUT%
@echo arquivo para consulta: %QUERY%
@echo --------------------------------------------------------------------------------
set /P outputfilename="Digite o nome do arquivo para saida: "
if [%outputfilename%] NEQ [] set OUTPUT="test/output/%outputfilename%" 

CLS
@echo arquivo para leitura: %INPUT%
@echo arquivo para consulta: %QUERY%
@echo arquivo para saida: %OUTPUT%
@echo --------------------------------------------------------------------------------
@echo Arvores Disponiveis:
@echo - AVL
@echo - BST ou ABP
@echo - CMP (estatisticas de ambas as arvores)
@echo. 

set /P treename="Digite a arvore para montar: "
if [%treename%] NEQ [] set TREE="%treename%"

@echo.
set /P timesinput="Digite quantas vezes a consulta deve repetir: "
if [%timesinput%] NEQ [] set TIMES="%timesinput%"


@echo on
%PROGRAM% %INPUT% %QUERY% %OUTPUT% %TREE% %TIMES%

CLS

@echo --------------------------------------------------------------------------------
@echo Arquivo de entrada: %INPUT%
@echo Arquivo de consulta: %QUERY%
@echo Arquivo de saida: %OUTPUT%
@echo Arvore usada: %TREE%
@echo.
@echo O programa executou com sucesso. Seu arquivo foi gerado em: 
@echo %OUTPUT%
@echo --------------------------------------------------------------------------------


@echo off
set /P option="Deseja abrir o arquivo criado? [s/n] "
call :option_passed %option% cond_false
notepad.exe %OUTPUT%
:cond_false

set /P option="Deseja testar novamente? [s/n] "
call :option_passed %option% cond_false_2
goto start

:cond_false_2
exit



REM função que recebe uma string OPÇÃO e um rotulo, 
REM caso a OPÇÃO seja SIM então termina, se não pula para o rotulo passado
:option_passed
	if ["%~1"] EQU ["s"] goto option_passed_end
	if ["%~1"] EQU ["S"] goto option_passed_end
	if ["%~1"] EQU ["sim"] goto option_passed_end
	if ["%~1"] EQU ["SIM"] goto option_passed_end
	goto %~2
	:option_passed_end
exit /B 0

pause
