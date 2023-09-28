object Main1 {


  def filterList(list: List[Double]) = {

    if (list.isEmpty) {
      throw new IllegalArgumentException("Список пуст")
    }

    var list1 = list.filter(x => Math.abs(x) <= 5)
    val result = sumList(list1)
    result
  }

  def sumList(list: List[Double]): Double = {
    var res = 0.0;
    if (list.isEmpty) 0.0
    else res = list.head + sumList(list.tail)
    res
  }

  def main(args: Array[String]): Unit = {
    var list = List[Double](1.0, 2.0, 3, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0);
    println(s"Cписок: ${list.toList}")

    println(s"Cумма элементов списка по модулю меньше 5: ${filterList(list)}")
  }
}