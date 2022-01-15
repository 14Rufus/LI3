package Info;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.Serializable;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.TreeMap;
import java.util.AbstractMap.SimpleEntry;

public class CatReviews implements Serializable, ICatReviews {
    //               businessID                 ano     mes               UserId   Review
    private HashMap<String,HashMap<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>>> catalogo;

    private String ficheiro;
    private int numeroTotalReviews;
    private int numeroReviewsErradas;
    private int reviewsSemImpacto;


    public CatReviews(HashMap<String,HashMap<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>>> catalogo, String ficheiro, int numeroTotalReviews, int numeroReviewsErradas, int reviewsSemImpacto) {
        this.catalogo = catalogo;
        this.ficheiro = ficheiro;
        this.numeroTotalReviews = numeroTotalReviews;
        this.numeroReviewsErradas = numeroReviewsErradas;
        this.reviewsSemImpacto = reviewsSemImpacto;
    }

    public CatReviews() {
        this.catalogo = new HashMap<String,HashMap<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>>>();
        this.ficheiro = "";
        this.numeroTotalReviews = 0;
        this.numeroReviewsErradas = 0;
        this.reviewsSemImpacto = 0;
    }

    public HashMap<String,HashMap<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>>> getCatalogo() {
        return this.catalogo;
    }

    public void setCatalogo(HashMap<String,HashMap<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>>> catalogo) {
        this.catalogo = catalogo;
    }

    public int getReviewsSemImpacto() {
        return reviewsSemImpacto;
    }

    public void setReviewsSemImpacto(int reviewsSemImpacto) {
        this.reviewsSemImpacto = reviewsSemImpacto;
    }

    public String getFicheiro() {
        return ficheiro;
    }

    public void setFicheiro(String ficheiro) {
        this.ficheiro = ficheiro;
    }

    public int getNumeroTotalReviews() {
        return numeroTotalReviews;
    }

    public void setNumeroTotalReviews(int numeroTotalReviews) {
        this.numeroTotalReviews = numeroTotalReviews;
    }

    public int getNumeroReviewsErradas() {
        return numeroReviewsErradas;
    }

    public void setNumeroReviewsErradas(int numeroReviewsErradas) {
        this.numeroReviewsErradas = numeroReviewsErradas;
    }


    //HashMap<String,HashMap<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>>> 
    public void putR(Review review){
        SimpleEntry<Integer,Integer> data = new SimpleEntry<>(review.getYear(),review.getMonth());
        if(!this.catalogo.containsKey(review.getBusiness_id())){
            List<Review> reviews =new ArrayList<>();
            reviews.add(review);
            HashMap<SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>> mapmeio = new HashMap<>();
            TreeMap<String,List<Review>> mapDentro  = new TreeMap<>();
            mapDentro.put(review.getUser_id(), reviews);
            mapmeio.put(data, mapDentro);
            catalogo.put(review.getBusiness_id(), mapmeio);
        }
        else{
            
            if(!this.catalogo.get(review.getBusiness_id()).containsKey(data)){
                List<Review> reviews =new ArrayList<>();
                reviews.add(review);
                TreeMap<String,List<Review>> mapDentro  = new TreeMap<>();
                mapDentro.put(review.getUser_id(), reviews);
                catalogo.get(review.getBusiness_id()).put(data, mapDentro);
            }
            else{
                if(!this.catalogo.get(review.getBusiness_id()).get(data).containsKey(review.getUser_id())){
                    List<Review> reviews =new ArrayList<>();
                    reviews.add(review);
                    catalogo.get(review.getBusiness_id()).get(data).put(review.getUser_id(), reviews);
                }
                else{
                    catalogo.get(review.getBusiness_id()).get(data).get(review.getUser_id()).add(review);
                }
            }
        }
    }


   
    public void parseReviews(String path, CatUsers u, CatBusiness b, String divisor) throws IOException {
        BufferedReader br = null;
        String line;
        try {
            br = new BufferedReader(new FileReader(path));
            br.readLine();
            while ((line = br.readLine()) != null) {
                Review rev = new Review();
                String [] buffer = line.split(divisor);
                if(buffer.length == 9 && u.exist(buffer[1]) && b.exist(buffer[2]))
                {
                    rev.setId(buffer[0]);
                    rev.setUser_id(buffer[1]);
                    rev.setBusiness_id(buffer[2]);
                    rev.setStars(Float.parseFloat(buffer[3]));
                    rev.setUseful(Integer.parseInt(buffer[4]));
                    rev.setFunny(Integer.parseInt(buffer[5]));
                    rev.setCool((Integer.parseInt(buffer[6])));
                    SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
                    Date data = sdf.parse(buffer[7]);
                    rev.setData(data);
                    rev.setText(buffer[8]);
                    this.putR(rev);

                    if ( Integer.parseInt(buffer[4]) + Integer.parseInt(buffer[5]) + Integer.parseInt(buffer[6]) == 0 ) this.reviewsSemImpacto++;

                } else this.numeroReviewsErradas++;

            }

        } catch (ParseException e) {
            e.printStackTrace();
        }

        br.close();
    }

}