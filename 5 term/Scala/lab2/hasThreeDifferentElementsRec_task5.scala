object Main5 {

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

  def main(args: Array[String]): Unit = {
    var list = List[Double](1.0, 2.0, 3, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0);
    println(s"Cписок: ${list.toList}")

    println(s"Проверки на наличие трех разных элементов в списке: ${hasThreeDifferentElementsRec(list)}")
  }
}