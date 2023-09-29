object Main4 {

  def containsSquareRec(list: List[Double]): Boolean = {
    if (list.isEmpty) {
      false
    } else {
      val currentElement = list.head

      if (list.exists(x => Math.sqrt(x) == currentElement) || list.exists(x =>  Math.sqrt(currentElement) == x )  ) {
        true
      } else {
        containsSquareRec(list.tail)
      }
    }
  }

  def main(args: Array[String]): Unit = {
    var list = List[Double](3.0, 3.0, 5.0, 6.0, 7.0, 8.0, 8.0, 10.0,4,16);
    println(s"Cписок: ${list.toList}")

    println(s"Cписок содержит квадрат одного из своих элементов: ${containsSquareRec(list)} ")
  }
}