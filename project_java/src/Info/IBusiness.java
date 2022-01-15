package Info;
import java.util.*;

public interface IBusiness  {
    String getId();
    String getName();
    String getCity();
    String getBusinessState();
    List<String> getBusinessCategories();
    int getBusinessNcategories();
    void setId(String id);
    void setName(String name);
    void setCity(String city);
    void setState(String state);
    void setNcategories(int ncategories);
    int compareTo(Object b);
}
