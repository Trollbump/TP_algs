Tasks:

Общие требования для всех задач  
Ввод/вывод отделены от решения.

Не должно быть утечек памяти, за каждую утечку памяти - штраф “-1”.

1_2. Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин. Вначале вводится количество вершин, затем последовательно целочисленные координаты всех вершин в порядке обхода против часовой стрелки.
n < 1000, координаты < 10000.
Указание. Для вычисления площади n-угольника можно посчитать сумму ориентированных площадей трапеций под каждой стороной многоугольника.  
Требования: Координата должна быть реализована в виде структуры.  

in  
3  
0 1  
1 0  
2 2  

out  
1.5

2_2. Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают, а на интервале [m, n-1] строго убывают. Найти m за O(log m).  
Требования:  Время работы O(log m).  
Внимание! В этой задаче сначала нужно определить диапазон для бинарного поиска размером порядка m с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.  
2 ≤ n ≤ 10000.  

in  
10  
1 2 3 4 5 6 7 6 5 4  

out  
6  

Задача № 3
Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.  
Формат входных данных.  
В первой строке количество команд n. n ≤ 1000000.  
Каждая команда задаётся как 2 целых числа: a b.  
a = 1 - push front  
a = 2 - pop front  
a = 3 - push back  
a = 4 - pop back  
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.  
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.  
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.   
Формат выходных данных.  
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.  

3_2. Реализовать дек с динамическим зацикленным буфером.  
Требования: Дек должен быть реализован в виде класса.  

in  
3  
1 44  
3 50  
2 44  

out  
YES  

in  
2  
2 -1  
1 10  

out  
YES  

in  
2  
3 44  
4 66  

out  
NO  


Требование для всех вариантов Задачи 4  
Решение всех задач данного раздела предполагает использование кучи, реализованной в виде класса. Решение должно поддерживать передачу функции сравнения снаружи.  
Куча должна быть динамической.  

4_1. Жадина.  
Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.  
Определить за сколько подходов Вовочка съест все фрукты в корзине.  
Формат входных данных. Вначале вводится n - количество фруктов и n строк с массами фруктов. Затем K - "грузоподъемность".  
Формат выходных данных. Неотрицательное число - количество подходов к корзине.  

in  
3  
1 2 2  
2  

out  
4  

in  
3  
4 3 5  
6  

out  
5  

in  
7  
1 1 1 1 1 1 1  
3  

out  
3  


Задача № 6 (3 балла)  
Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.  
Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.  

Требования:  
К дополнительной памяти: O(n).  
Среднее время работы: O(n).  
Должна быть отдельно выделенная функция partition.  
Рекурсия запрещена.  
Решение должно поддерживать передачу функции сравнения снаружи.

6_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”.  
Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.

in
10 4  
1 2 3 4 5 6 7 8 9 10  

out  
5  

in  
10 0  
3 6 5 7 2 9 8 10 4 1  

out
1  

in  
10 9  
0 0 0 0 0 0 0 0 0 1  

out  
1  

Задача 1. Хеш-таблица  
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.  
Хранимые строки непустые и состоят из строчных латинских букв.  
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.  
Начальный размер таблицы должен быть равным 8-ми.  
Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.  
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.  

1_2. Для разрешения коллизий используйте двойное хеширование.  
Требования: В таблице запрещено хранение указателей на описатель элемента.  

Формат входных данных  
Каждая строка входных данных задает одну операцию над множеством.  
Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.  
Тип операции  – один из трех символов:  
    +  означает добавление данной строки в множество;  
    -  означает удаление  строки из множества;  
    ?  означает проверку принадлежности данной строки множеству.  
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.  
При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.  

Формат выходных данных  
Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того, встречается ли данное слово в нашем множестве.  
stdin  
\+ hello  
\+ bye  
\? bye  
\+ bye  
\- bye  
\? bye  
\? hello  

stdout  
OK  
OK  
OK  
FAIL  
OK  
FAIL  
OK  

Задача 2. Порядок обхода  
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.  
Требуется построить бинарное дерево, заданное наивным порядком вставки.  
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.  
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.  

2_2. Выведите элементы в порядке pre-order (сверху вниз).  
in  
3  
2 1 3  

out  
2 1 3  

in  
3  
1 2 3  

out  
1 2 3  

in  
3  
3 1 2  

out  
3 1 2  

in  
4  
3 1 4 2  

out  
3 1 2 4  


Задача 4. Использование АВЛ-дерева  
Требование для всех вариантов Задачи 4  
Решение должно поддерживать передачу функции сравнения снаружи.  

4_1. Солдаты. В одной военной части решили построить в одну шеренгу по росту.  
Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.  
Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие.  
За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста. 
Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становиться.  

Требования: скорость выполнения команды - O(log n).  

Формат входных данных.  
Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000).  
В каждой следующей строке содержится описание команды:  
число 1 и X если солдат приходит в строй (X – рост солдата, натуральное число до 100 000 включительно) и число 2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя. Солдаты в строе нумеруются с нуля.  

Формат выходных данных.  
На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции, на которую должен встать этот солдат (все стоящие за ним двигаются назад).  

in  
5  
1 100  
1 200  
1 50  
2 1  
1 150  

out  
0  
0  
2  
1  


Общие требования для всех задач  
Ввод/вывод отделены от решения.  
Не должно быть утечек памяти.  

Задача 1. «Представление графа».  
Дан базовый интерфейс для представления ориентированного графа:  

```struct IGraph {
virtual ~IGraph() {}
    
    // Добавление ребра от from к to.
virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

virtual std::vector<int> GetNextVertices(int vertex) const = 0;
virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};
```

Необходимо написать несколько реализаций интерфейса:  
ListGraph, хранящий граф в виде массива списков смежности,  
MatrixGraph, хранящий граф в виде матрицы смежности,  
SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,  
ArcGraph, хранящий граф в виде одного массива пар {from, to}.  
Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.  
Для каждого класса создавайте отдельные h и cpp файлы.  
Число вершин графа задается в конструкторе каждой реализации.  


Задача 2. Количество различных путей  
Дан невзвешенный неориентированный граф.  
В графе может быть несколько кратчайших путей между какими-то вершинами.  
Найдите количество различных кратчайших путей между заданными вершинами.  

Требования: сложность O(V+E).  

Формат ввода.  
v: кол-во вершин (макс. 50000),  
n: кол-во ребер (макс. 200000),  
n пар реберных вершин,  
пара вершин u, w для запроса.  

Формат вывода.  
Количество кратчайших путей от u к w.  

in  
4  
5  
0 1  
0 2  
1 2  
1 3  
2 3  

0 3  

out  
2  


Задача 3. «Города»  
Требуется отыскать самый выгодный маршрут между городами.  
Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.  
Формат входных данных.  
Первая строка содержит число N – количество городов.  
Вторая строка содержит число M - количество дорог.  
Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).  
Последняя строка содержит маршрут (откуда и куда нужно доехать).  

Формат выходных данных.  
Вывести длину самого выгодного маршрута.  

in  
6  
9  
0 3 1  
0 4 2  
1 2 7  
1 3 2  
1 4 3  
1 5 3  
2 5 3  
3 4 4  
3 5 6  
0 2  

out  
9  


Задача 4. «Пятнашки»  
Написать алгоритм для решения игры в “пятнашки”.  
Решением задачи является приведение к виду:  
```[ 1  2  3  4 ]  
[ 5  6  7  8 ]  
[ 9  10 11 12]  
[ 13 14 15 0 ]  
```
где 0 задает пустую ячейку.  
Достаточно найти хотя бы какое-то решение. Число перемещений костяшек не обязано быть минимальным.  

Формат входных данных  
Начальная расстановка.  

Формат выходных данных  
Если решение существует, то в первой строке выходного файла выведите минимальное число перемещений костяшек, которое нужно сделать, чтобы достичь выигрышной конфигурации,  
а во второй строке выведите соответствующую последовательность ходов:  
L означает, что костяшка сдвинулась влево,  
R – вправо,  
U – вверх,  
D – вниз.  
Если таких последовательностей несколько, то выведите любую из них.  
Если же выигрышная конфигурация недостижима, то выведите в выходной файл одно число −1.  

in  
1 2 3 4  
5 6 7 8  
9 10 11 0  
13 14 15 12  

out  
1  
U  

