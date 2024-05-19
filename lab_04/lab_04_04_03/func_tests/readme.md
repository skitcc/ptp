# Тесты для лабораторной работы No04_01
## Входные данные
Телефонный номер
## Выходные данные
YES / NO
## Позитивные тесты:
- 01 - Обычный номер телефона
- 02 - Код страны без +
- 03 - Кода страны нет
- 04 - Пробельные символы перед обычным телефоннным номером
- 05 - Код страны содержит символ
- 06 - Код оператора не 3 цифры
- 07 - Вместо дефиса после кода оператора не дефис
- 08 - Нет открывающей скобки кода оператора
- 09 - Нет закрывающей скобки кода оператора
- 10 - Цифр после кода оператора не 3
- 11 - В цифрах после кода оператора есть символ
- 12 - Не дефис после трех цифр после кода оператора
- 13 - Препоследнее кол-во цифр не 2
- 14 - В преддпоследнем кол-ве есть символ
- 15 - После предпоследней пары не дефис
- 16 - Последнее кол-во цифр не 2
- 17 - В последнем кол-ве цифр есть символ
- 18 - После номера есть мусор 
- 19 - Перед номером есть мусор
- 20 - После номера есть пробельные символы




## Негативные тесты:
- 01 - длина строки больше чем 256 символов