object Main6 {

  def countWordsStartingWithUpperCase(text: String): Int = {
    val words = text.split("\\s+")
    words.count(word => word.nonEmpty && word(0).isUpper)
  }

  def main(args: Array[String]): Unit = {
    val text = "Hello to Ronny old nail"
    val result = countWordsStartingWithUpperCase(text)
    println(s"Число слов, начинающихся с большой буквы: $result")


  }
}