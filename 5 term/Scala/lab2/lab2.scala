object Lab2 {


  def summaList( list : List[Double]) = {

    var result = 0.0;

    var list1 = list.filter(x => Math.abs(x) <= 5)

    list1.map(el => result = result + el);

    result
  }

  def summaEvenNumber( list : List[Double]) = {

    var res = 0.0
    for (i <- list.indices if i % 2 == 0) {
        res = res + list(i)
    }
    res
  }

  def findClosestNumber(list: List[Double], target: Double): Double = {
    val index = list.indexOf(list.minBy(x => Math.abs(x - target)))
    index
  }

  def indexAverageNumber(list: List[Double]) = {

    var res: Double = 0
    var average: Double = 0

    list.map(el => res = res + el)

    average = res / list.size

    val index = findClosestNumber(list,average)

    index
  }


  def containsSquare(list: List[Double]): Boolean = {
    list.exists(x => list.contains(x * x))
  }


  def checkNumberOnDiffentValues(list: List[Double]): Boolean = {

  }

  def main(args: Array[String]): Unit = {

    var list =  List[Double](5.0,1.0,7.0,7.0,1.0)
    println(s"\nCумма элементов списка по модулю меньше 5: ${summaList(list)}" )

    var list1 = List[Double](1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,9.0)

    println(s"\nCумма каждого второго элемента: ${summaEvenNumber(list1)}")

    println(s"\nИндекс элемента, наименее отклоняющегося от среднего значения: ${indexAverageNumber(list)}");

    println(s"\nCписок содержит квадрат одного из своих элементов: ${containsSquare(list1)}")

    println(s"\nПроверки на наличие трех разных элементов в списке: ${checkNumberOnDiffentValues(list1)}")

  }
}