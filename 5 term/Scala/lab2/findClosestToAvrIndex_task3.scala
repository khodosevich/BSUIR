object Main3 {

  def findClosestToAverageIndexRec(list: List[Double], currentIndex: Int = 0, closestIndex: Int = 0, minDiff: Double = Double.MaxValue, average: Double = 0): Int = {

    if (list.isEmpty) {
      throw new IllegalArgumentException("Список пуст")
    }else{
      if (currentIndex >= list.length) closestIndex
      else {
        val currentElement = list(currentIndex)
        val diff = Math.abs(currentElement - average)
        if (diff < minDiff) {
          findClosestToAverageIndexRec(list, currentIndex + 1, currentIndex, diff, average)
        } else if (diff == minDiff && currentElement < list(closestIndex)) {
          findClosestToAverageIndexRec(list, currentIndex + 1, currentIndex, diff, average)
        } else {
          findClosestToAverageIndexRec(list, currentIndex + 1, closestIndex, minDiff, average)
        }
      }
    }
  }

  def main(args: Array[String]): Unit = {
    val list = List(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0)

    var sum : Double = 0;

    for(element <- 0 to list.length){
      sum = sum + element
    }

    val avg = sum / list.length

    println(s"Индекс наименее отклоняющегося от среднего: ${findClosestToAverageIndexRec(list , average = avg)}")
  }
}