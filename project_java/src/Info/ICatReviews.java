package Info;

import java.io.IOException;
import java.util.AbstractMap;
import java.util.HashMap;
import java.util.List;
import java.util.TreeMap;

public interface ICatReviews {
    HashMap<String, HashMap<AbstractMap.SimpleEntry<Integer,Integer>, TreeMap<String, List<Review>>>> getCatalogo();
    void setCatalogo(HashMap<String,HashMap<AbstractMap.SimpleEntry<Integer,Integer>, TreeMap<String,List<Review>>>> catalogo);
    int getReviewsSemImpacto();
    String getFicheiro();
    void setFicheiro(String ficheiro);
    int getNumeroTotalReviews();
    int getNumeroReviewsErradas();
    void putR(Review review);
    void parseReviews(String path, CatUsers u, CatBusiness b, String divisor) throws IOException;

}
