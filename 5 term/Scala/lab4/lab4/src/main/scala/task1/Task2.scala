package task1

import org.apache.spark.sql.{Encoders, SparkSession}

object Task2 extends App{

  var encoder = Encoders.kryo[String]
  val spark = SparkSession.builder().master("local[*]").appName("lab4").getOrCreate()

  val data = spark.read.textFile("src/main/scala/task1/text")

  val wordsRDD = data.flatMap(l => l.split("\\s"))(encoder)

  val pattern = ".*\\b.*(?:prog).*\\b.*".r

  val filteredWordsRDD2 = wordsRDD.filter(word => pattern.pattern.matcher(word).matches())

  filteredWordsRDD2.collect().foreach(println)

}
