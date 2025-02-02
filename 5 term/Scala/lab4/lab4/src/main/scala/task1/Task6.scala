package task1

import org.apache.spark.sql.{Encoders, SparkSession}

object Task6 extends App{

  var encoder = Encoders.kryo[String]
  val spark = SparkSession.builder().master("local[*]").appName("lab4").getOrCreate()

  val data = spark.read.textFile("src/main/scala/task1/text")


  val wordsRDD = data.flatMap(l => l.split("\\s"))(encoder)

  val lastWord = wordsRDD.rdd.collect()

  if(lastWord.length >= 1){
      println(lastWord(lastWord.length - 1))
  }


}
