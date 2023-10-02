object Main4 {
  def main(args: Array[String]): Unit = {
    val text = "big black cat runs after small poor catty."
    val words = text.split(" ").toList
    val shuffledWords = util.Random.shuffle(words)

    val replacedWords = shuffledWords
      .updated(0, shuffledWords(3))
      .updated(1, shuffledWords(6))
      .updated(2, shuffledWords(5))

    val resultString = replacedWords.mkString(" ")
    println(resultString)

  }
}