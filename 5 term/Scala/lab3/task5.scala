object Main5 {

  def findDoubledConsonants(text: String): List[String] = {
    val regex = """(?i)([b-df-hj-np-tv-z])\1""".r
    regex.findAllIn(text).toList
  }

  def main(args: Array[String]): Unit = {
    val text = "Hello to Ronny old nail"
    val doubledConsonants = findDoubledConsonants(text)

    doubledConsonants.foreach(println)
  }
}