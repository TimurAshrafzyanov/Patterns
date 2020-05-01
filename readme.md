# Patterns

Файл ArchitectureDiagram.drawio - диалграмма с архитектурой проекта
Открывать с сайта https://app.diagrams.net/

Запуск проекта:
mkdir build
cd build
cmake ..
make
../bin/Game

Список конманд:
Commands :
	- help

		Prints help menu.
		Doesn`t spend a step. 

	- map 

		Prints game map.
		Doesn`t spend a step.

	- army

		Prints players army.
		Doesn`t spend a step.

	- balance

		Prints your balance.
		Doesn`t spend a step.

	- go [left / right / up / down]

		Changes players cords ([left / right] changes x cord,
			[up / down] changes y cord).
		Spends a step.

	- attack 

		Your army attacks enemy`s army, if it is near.
		Spends a step.

	- new
	    line

		Makes new line.
		Doesn`t spend a step.

	    squad //number_of_line//

		Makes new squad in line //number_of_line//.
		Doesn`t spend a step.

	    unit [w / a / h] //number_of_line// //number_of_squad//

		Makes new unit in line //number_of_line// 
			in squad //number_of_squad//.
		w - Warior, a - Archer, h - Harseman.
		Spends a step.

	- recharge
		
		Units recharges, player gets *2 coins.
		Spends a step.

	- move //number_of_line_from// //number_of_squad_from// 
	    //number_of_unit//
	    //number_of_line_to// //number_of_squad_to//

		Moves unit //number_of_unit//
		from line //number_of_line_from//, 
			squad //number_of_squad_from// 
		to line //number_of_line_to//, 
			squad //number_of_squad_to//.
		Spends a step.

	- progress

		Increases count of coins you get per step.
		You can use it no more than once every five steps.
		If your last step was attack, you can`t use it.
