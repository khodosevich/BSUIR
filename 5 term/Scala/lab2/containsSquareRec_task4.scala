object Main4 {

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


  def main(args: Array[String]): Unit = {
    var list = List[Double](1.0, 2.0, 3, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0);
    println(s"Cписок: ${list.toList}")

    println(s"Cписок содержит квадрат одного из своих элементов: ${containsSquareRec(list)} ")
  }
}