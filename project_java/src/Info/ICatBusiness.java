package Info;

import java.io.IOException;
import java.util.HashMap;
import java.util.TreeMap;

public interface ICatBusiness {
    HashMap<Character, TreeMap<String,Business>> getCatalogo();
    String getFicheiro();
    void setFicheiro(String ficheiro);
    int getNumeroTotalBusinesses();
    void putB(String key, Business business);
    void parseBusiness(String path, String div) throws IOException;
    boolean exist(String id);
}
