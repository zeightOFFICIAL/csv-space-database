
# MyPlanets

## CSV база данных различных космических объектов с режимами просмотра, редактирования и создания

## Приложение собрано на C++ с помощью среды Qt6

### Автор: А.В. Саганенко

#### Санкт-Петербургский государственный университет телекоммуникаций им. проф. М. А. Бонч-Бруевича

### Описание

Десктопное приложения для управления csv-баз данных. База данных предоставляет собой информацию о различных космических объектах: планетах, звездах, галактиках и так далее. Из представленной информации: название, тип, подтип, радиус, вес, кол-во спутников, население, период вращения, температура. Приложение реализовано на Qt6.3.0 на C++. Главные элементы модели - классы контейнеры: STL's vector, Qt's QStringList, разработанная самостоятельно queue. Присутствуют три отдельных режима работы программы: просмотр, редактирование, создание.

### Заметки для разработки

* ЯП: C++/C (>11)
* Среда разработки: Qt 6.3.0
* Компилятор: MinGw 11.2.0 64bit
* Дебаггер: GNU gdb 11.2.0
* CMake: CMake 3.21.1 Qt
* ОС разработки: Windows 10 (19044)

Режим просмотра использует QStringList класс среды Qt, режим создания использует класс контейнер Queue описанный в queue.h, режим редактирования использует vector стандартной библиотеки STL. Большинство ошибок было обнаружено в режиме редактирования. Будьте внимательны при работе с парсингом и открытием/сохранением файлов (баз данных). В общем случае, все должно работать правильно. Обратите внимание, что оптимизация должна быть улучшена для функций загрузки и сохранения. Следует также провести работу с подгрузкой и в целом с изображениями.

### Условия запуска

* Для запуска, исправления ошибок и тестирования, обновления, написания и разработки новых функций откройте MyPlanets.pro в Qt Creator. Сборка в отладочную или релизную версию. Последняя совместимая версия — 6.3.0. Вероятно, совместим с более старыми или новыми версиями, но лучше не использовать с < Qt5 и > Qt7. При разработке и оптимизации стоит обратить внимание на режим редактирования, так как в нем большое подводных камней. Также имейте в виду, что queue.h — это разработанный с нуля контейнер класс, обязательно его прочитайте при работе с режимом создания БД. Используйте source файлы из папки src; используйте файлы разметки из папки forms
* Для запуска в режиме релиза используйте сгенерированный MyPlanets.exe, который будет присутствовать в релизе. Все DLL критически необходимы. Проверено на чистой Win10 22H2 64bit. Поэтому exe должен быть совместим с большинством систем.

### Функционал

* Просмотр баз данных. Отображается каждое поле строки, каждое изображение. Базы данных должны быть созданы в этом же приложении и иметь формат csv либо txt. Навигация через кнопки в нижней части окна или список в верхней части окна. Открытие других режимов выполняется через menubar в верхней части окна
* Просмотр CSV файла
* Создание баз данных. Возможен ввод каждого поля, выбор изображения. Присутствует предварительный просмотр итогового файла. Возможна очистка полей и базы данных, сохранение базы данных в выбранное место на диске
* Редактирование баз данных. Изменить любой столбец любой строки базы данных. 
Добавление новых строк, удаление старых. Сохранение базы данных. Объединение нескольких баз данных в одну. Навигация через список
* Обработана большая часть исключений. Простая навигация. Наглядность.

##### Больше информации в Doc_RU.pdf