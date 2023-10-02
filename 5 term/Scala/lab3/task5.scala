object Main5 {

  def findDoubledConsonants(text: String): List[String] = {
    val consonants = "bcdfghjklmnpqrstvwxyz"
    val matches = for {
      i <- 0 until text.length - 1
      if consonants.contains(text(i).toLower) && consonants.contains(text(i + 1).toLower) && text(i) == text(i + 1)
    } yield text.substring(i, i + 2)
    matches.toList
  }
  def main(args: Array[String]): Unit = {
    val text = "Hello to Ronny old nail"
    val doubledConsonants = findDoubledConsonants(text)

    doubledConsonants.foreach(println)
  }
}