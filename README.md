### Запуск:
    Запускаем исполняемый файл.
### Входные данные:
    Количество правил N в грамматике. В следующих N строках записаны правила в виде "<нетерминал><пробел><правая часть правила>". В последней строке вводится слово, которое надо обработать.
### Выходные данные:
    "Yes", если слово принадлежит грамматике, и "No" иначе.
### Формат правил:
    В качестве нетерминалов могут быть использованы большие буквы латинского алфавита и "S'", в качестве начального правила. Алфавит - маленькие латинские буквы.   
### Тесты: 
Тесты лежат в файле "test_in.txt"\
В первой строк записано количество тестов, в конце каждого теста записано 1, если слово выводимо в грамматике, и 0 иначе.
Тестирование запускается флагом -t \
Пример: ./a.out -t \
Результаты тестов записываются в файл "test_out.txt", на экран выводится количество пройденных тестов
