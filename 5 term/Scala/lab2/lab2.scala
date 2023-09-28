object Lab2 {

  def sumList(list: List[Double]): Double = {
    var res = 0.0;
    if (list.isEmpty) 0.0
    else res = list.head + sumList(list.tail)
    res
  }

  def filterList(list: List[Double]) = {

    if (list.isEmpty) {
      throw new IllegalArgumentException("Список пуст")
    }

    var list1 = list.filter(x => Math.abs(x) <= 5)
    val result = sumList(list1)
    result
  }


  def summaEvenNumber(list: List[Double], index: Int = 0, result: Double = 0): Double = {

    if (list.isEmpty) {
      throw new IllegalArgumentException("Список пуст")
    }

    if (index >= list.length) result
    else if (index % 2 == 0) summaEvenNumber(list, index + 1, result + list(index))
    else summaEvenNumber(list, index + 1, result)
  }


  def findClosestToAverageIndex(list: List[Double]): Int = {
    if (list.isEmpty) {
      throw new IllegalArgumentException("Список пуст")
    }

    val average = list.sum / list.length

    val closestElement = list.minBy(element => Math.abs(element - average))
    list.indexOf(closestElement)
  }

  def containsSquareRec(list: List[Double]): Boolean = {
    if (list.isEmpty) {
      false
    }
    else {
      val currentElement = list.head
      if (Math.sqrt(currentElement) % 1 == 0) {
        true
      }
      else {
        containsSquareRec(list.tail)
      }
    }
  }


  def hasThreeDifferentElementsRec(list: List[Double], uniqueElements: Set[Double] = Set.empty, count: Int = 0): Boolean = {
    if (count >= 3) {
      true
    } else if (list.isEmpty) {
      false
    } else {
      val currentElement = list.head
      val updatedSet = uniqueElements + currentElement
      val updatedCount = if (uniqueElements.contains(currentElement)) count else count + 1

      hasThreeDifferentElementsRec(list.tail, updatedSet, updatedCount)
    }
  }


  def printMenu(): Unit = {
    print("\n1 - Cумма элементов списка по модулю меньше 5")
    print("\n2 - Cумма каждого второго элемента")
    print("\n3 - Индекс элемента, наименее отклоняющегося от среднего значения")
    print("\n4 - Cписок содержит квадрат одного из своих элементов")
    print("\n5 - Проверки на наличие трех разных элементов в списке")
    print("\n6 - Вывод спика")
    print("\n0 - Завершение программы\n")
  }

  def main(args: Array[String]): Unit = {

    var list = List[Double](1.0, 2.0, 3, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0);
    var x = 100

    println(s"Cписок: ${list.toList}")

    while (x != 0) {

      printMenu()

      var choice = scala.io.StdIn.readInt()

      choice match {
        case 1 => println(s"Cумма элементов списка по модулю меньше 5: ${filterList(list)}")
        case 2 => println(s"Cумма каждого второго элемента: ${summaEvenNumber(list)}")
        case 3 => println(s"Индекс элемента, наименее отклоняющегося от среднего значения:${findClosestToAverageIndex(list)} ")
        case 4 => println(s"Cписок содержит квадрат одного из своих элементов: ${containsSquareRec(list)} ")
        case 5 => println(s"Проверки на наличие трех разных элементов в списке: ${hasThreeDifferentElementsRec(list)}")
        case 6 => println(s"Cписок: ${list.toList}")
        case 0 => x = 0
        case _ => println("Некорректный выбор. Введите число от 0 до 8.")
      }
    }
  }
}