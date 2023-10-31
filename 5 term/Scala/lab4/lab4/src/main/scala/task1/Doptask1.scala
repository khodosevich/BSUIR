
package task1

import org.apache.spark.SparkConf
import org.apache.spark.SparkContext

// два предложения на англ. удалить пробелы 2 способами через регулярки
// утроить букву T в слове mother
// удалить все гласные с словах

object SparpDop {


 def deleteSpacesFirst():String={
  val sentenceWithoutSpaces1 = RDD_sentence.map(line => line.replaceAll("\\s", ""))
    println("\nSentence without spaces:")
    sentenceWithoutSpaces1.foreach(println)
 }

 def deleteSpacesSecond(): String = {
  val sentenceWithoutSpaces2 = RDD_sentence.map(line => line.replaceAll(" ", ""))
    println("\nSentence without spaces:")
    sentenceWithoutSpaces2.foreach(println)
 }

 def main(args : Array[String]): Unit = {
    val conf = new SparkConf()
      .setMaster("local[*]")
      .setAppName("SparkLab")
    val sc = new SparkContext(conf)

  val sentence = "This is a sample sentence with spaces. My name is Max."
  val RDD_sentence = sc.parallelize(Seq(sentence))

    deleteSpacesFirst()
    deleteSpacesSecond()

    // утроение буквы Т
    val word = "Mother"
    val wordWithTripleT = sc.parallelize(Seq(word)).map(line => line.replaceAll("t", "ttt"))
    println("\nWord with triple 't':")
    wordWithTripleT.foreach(println)

    // удаление гласных
    val sentenceWithoutVowels = RDD_sentence.map(line => line.replaceAll("[aeiouyAEIOUY]", ""))
    println("\nSentence without vowels:")
    sentenceWithoutVowels.foreach(println)
 }
}

