import scala.collection.mutable.ListBuffer

object Main6 {

  def merge(firstList: List[Int], secondList: List[Int], buffer: ListBuffer[Int]): List[Int] = {
    if (!firstList.isEmpty) {
      buffer += firstList.head
      return merge(firstList.tail, secondList, buffer)
    } else if (!secondList.isEmpty) {


      buffer += secondList.head


      return merge(firstList, secondList.tail, buffer)
    } else buffer.toList
  }

  def summaEvenNumber(list: List[Int], index: Int = 0, result: Double = 0): Double = {

    if (list.isEmpty) {
      throw new IllegalArgumentException("Список пуст")
    }

    if (index >= list.length) result
    else if (index % 2 == 1) summaEvenNumber(list, index + 1, result + list(index))
    else summaEvenNumber(list, index + 1, result)
  }


  def main(args: Array[String]): Unit = {
    val list1 = List(1, 2, 3)
    val list2 = List(4, 5, 6)

    val buffer = ListBuffer[Int]()
    val mergedList = merge(list1, list2, buffer)

    println(mergedList)


    println(summaEvenNumber(mergedList))


  }
}