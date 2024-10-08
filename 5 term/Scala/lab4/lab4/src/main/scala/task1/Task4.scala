package task1

import org.apache.spark.sql.{Encoders, SparkSession}
import task1.Task4.filteredWordsRDD4

object Task4 extends App{

  var encoder = Encoders.kryo[String]
  val spark = SparkSession.builder().master("local[*]").appName("lab4").getOrCreate()

  val data = spark.read.textFile("src/main/scala/task1/text")


  val wordsRDD = data.flatMap(l => l.split("\\s"))(encoder)

  val pattern = "\\b\\w{2}r\\w*\\b".r
  val filteredWordsRDD4 = wordsRDD.filter(word => pattern.pattern.matcher(word).matches)

  filteredWordsRDD4.collect().foreach(println)



}
