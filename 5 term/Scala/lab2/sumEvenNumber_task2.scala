object Main2 {

  def summaEvenNumber(list: List[Double], index: Int = 0, result: Double = 0): Double = {

    if (list.isEmpty) {
      throw new IllegalArgumentException("Список пуст")
    }

    if (index >= list.length) result
    else if (index % 2 == 0) summaEvenNumber(list, index + 1, result + list(index))
    else summaEvenNumber(list, index + 1, result)
  }


  def main(args: Array[String]): Unit = {
    var list = List[Double](1.0, 2.0, 3, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0);
    println(s"Cписок: ${list.toList}")

    println(s"Cумма каждого второго элемента: ${summaEvenNumber(list)}")
  }
}