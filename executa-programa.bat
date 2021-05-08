@echo off

set PROGRAM="bin/Debug/Buscador de Palavras Chave.exe"
set INPUT="test/input/100.txt"
set QUERY="test/query/10.txt"
set OUTPUT="test/output/10-CMP.txt"
set TREE="CMP"

@echo arquivos para entrada:
dir /b "test/input/"
@echo. 

set /P inputfilename="Arquivo de leitura: "
if [%inputfilename%] NEQ [] set INPUT="test/input/%inputfilename%"

@echo. 
@echo arquivos para consulta:
dir /b "test/query/"
@echo. 

set /P queryfilename="Arquivo de consulta: "
if [%queryfilename%] NEQ [] set QUERY="test/query/%queryfilename%"

set /P outputfilename="Arquivo de saida: "
if [%outputfilename%] NEQ [] set OUTPUT="test/output/%outputfilename%"

@echo.
@echo Arvores Disponiveis:
@echo - AVL
@echo - BST ou ABP
@echo - CMP (estatisticas de ambas as arvores)
@echo. 

set /P treename="Arvore: "
if [%treename%] NEQ [] set TREE="%treename%"


@echo on
%PROGRAM% %INPUT% %QUERY% %OUTPUT% %TREE%

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

pause
