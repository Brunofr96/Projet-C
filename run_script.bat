gu@echo off
REM Suppression des fichiers précédents
if exist main.o del main.o
if exist parser.o del parser.o
if exist generator.o del generator.o
if exist drawplus.exe del drawplus.exe

REM Compilation des fichiers C
echo Compilation de main.c...
gcc -c src\main.c -o main.o
if errorlevel 1 goto :error

echo Compilation de parser.c...
gcc -c src\parser.c -o parser.o
if errorlevel 1 goto :error

echo Compilation de generator.c...
gcc -c src\generator.c -o generator.o
if errorlevel 1 goto :error

REM Liaison des objets pour créer l'exécutable
echo Création de l'exécutable...
gcc main.o parser.o generator.o -o drawplus
if errorlevel 1 goto :error

REM Exécution du script Python
echo Lancement du script Python...
python ui.py
if errorlevel 1 goto :error

REM Fin de l'exécution
echo Opération terminée avec succès !
goto :end

:error
echo Une erreur s'est produite. Vérifiez votre code ou vos commandes.
pause
exit /b 1

:end
pause
