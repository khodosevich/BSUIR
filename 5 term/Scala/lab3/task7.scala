object Main7 {

  def countOccurrences(text: String, target: Char): Int = {
    text.count(_ == target)
  }


  def main(args: Array[String]): Unit = {
    val text = "Hello to everybody"
    val charToCount = 'o'
    val result = countOccurrences(text, charToCount)

    println(s"Число вхождений буквы '$charToCount': $result")
  }
}