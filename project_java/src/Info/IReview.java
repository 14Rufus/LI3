package Info;

import java.util.*;

public interface IReview {
    String getId();
    String getUser_id();
    String getBusiness_id();
    float getStars();
    int getUseful();
    int getFunny();
    int getCool();
    Date getData();
    String getText();
    void setId(String id);
    void setUser_id(String user_id);
    void setBusiness_id(String business_id);
    void setStars(float stars);
    void setUseful(int useful);
    void setFunny(int funny);
    void setCool(int cool);
    void setData(Date data);
    void setText(String text);
    int compareTo(Object r);
}
