@echo off
@echo arquivos para usar contidos no diretorio test:
dir /b test
@echo. 
set /P input="Arquivo de leitura:"
if [%input%] EQU [] GOTO SKIP_ASK
set /P query="Arquivo de consulta:"
set /P output="Arquivo de saida:"
:SKIP_ASK
@echo on
if [%input%] EQU [] (
	"bin/Debug/Buscador de Palavras Chave.exe" "test/base_100.txt" "test/consulta_100.txt" "output.txt"
) else (
	"bin/Debug/Buscador de Palavras Chave.exe" "%input%" "%query%" "%output%"
)
pause
