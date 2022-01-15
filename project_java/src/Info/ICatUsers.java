package Info;

import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.TreeMap;

public interface ICatUsers {
    HashMap<Character, TreeMap<String,User>> getCatalogo();
    String getFicheiro();
    void setFicheiro(String ficheiro);
    int getNumeroTotalUsers();
    void putU(String key, User user);
    void parseUsers(String path, String div) throws FileNotFoundException;
    boolean exist(String id);
}
