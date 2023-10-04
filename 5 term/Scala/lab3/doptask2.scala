object Test1 {

  def findDoubledConsonants(text: String): List[String] = {
    val regex = """(?i)([b-df-hj-np-tv-z])\1""".r
    regex.findAllIn(text).toList
  }

  def main(args: Array[String]): Unit = {

    val text = "matvey hee yy hello"
    val doubledConsonants = findDoubledConsonants(text)

    println(s"Удвоенные согласные: $doubledConsonants")

  }
}