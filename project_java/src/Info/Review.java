package Info;

import java.io.Serializable;
import java.util.Calendar;
import java.util.Date;

public class Review implements Serializable, Compare, IReview {
    private String id;
    private String user_id;
    private String business_id;
    private float stars;
    private int useful;
    private int funny;
    private int cool;
    private Date data;
    private String text;

    public Review(){
        this.id = null;
        this.user_id = null;
        this.business_id = null;
        this.stars = 0;
        this.useful = 0;
        this.funny = 0;
        this.cool = 0;
        this.data = null;
        this.text = null;
    }

    public Review(String id, String user_id, String business_id, float stars, int useful, int funny, int cool,Date data, String text) {
        this.id = id;
        this.user_id = user_id;
        this.business_id = business_id;
        this.stars = stars;
        this.useful = useful;
        this.funny = funny;
        this.cool = cool;
        this.data = data;
        this.text = text;
    }

    public Review(Review r){
        this.id = r.id;
        this.user_id = r.user_id;
        this.business_id = r.business_id;
        this.stars = r.stars;
        this.useful = r.useful;
        this.funny = r.funny;
        this.cool = r.cool;
        this.data = r.getData();
        this.text = r.text;
    }

    public String getId() {
        return id;
    }

    public String getUser_id() {
        return user_id;
    }

    public String getBusiness_id() {
        return business_id;
    }

    public float getStars() {
        return stars;
    }

    public int getUseful() {
        return useful;
    }

    public int getFunny() {
        return funny;
    }

    public int getCool() {
        return cool;
    }

    public Date getData() {
        Object o = this.data.clone();
        return (Date) o;
    }

    public String getText() {
        return text;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void setUser_id(String user_id) {
        this.user_id = user_id;
    }

    public void setBusiness_id(String business_id) {
        this.business_id = business_id;
    }

    public void setStars(float stars) {
        this.stars = stars;
    }

    public void setUseful(int useful) {
        this.useful = useful;
    }

    public void setFunny(int funny) {
        this.funny = funny;
    }

    public void setCool(int cool) {
        this.cool = cool;
    }

    public void setData(Date data) {
        Object o = data.clone();
        this.data = (Date) o;
    }

    @Override
    public String toString() {
        return "Review -> id: " + id + '\n' +
                "User_id: " + user_id + '\n' +
                "Business_id: " + business_id + '\n' +
                "Stars: " + stars + '\n' +
                "Useful: " + useful + '\n' +
                "Funny: " + funny + '\n' +
                "Cool: " + cool + '\n' +
                "Data: " + data.toString() + '\n' +
                "Review: " + text + '\n';
    }

    public void setText(String text) {
        this.text = text;
    }

    public Review clone(){
        return new Review(this);
    }

    @Override
    public int compareTo(Object r) {
        Review r1 = (Review) r;
        if (this.getId().equals( r1.getId()))
            return 0;
        else
            return 1;
    }

    //extract individual fields of year,month, day
    public int getYear(){
        Date date = this.data;
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(date);
        return calendar.get(Calendar.YEAR);
    }


    public int getMonth(){
        Date date = this.data;
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(date);
        return calendar.get(Calendar.MONTH);
    }

}
