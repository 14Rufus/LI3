package Info;

import java.io.Serializable;
import java.util.*;

public class Stats implements Serializable, IStats {
    private String ficheiroU;
    private String ficheiroB;
    private String ficheiroR;
    private int wrongReviews;
    private int totalReviews;
    private int reviewsSemImpacto;
    private int totalBusinesses;
    private int totalBusinessesAvaliados;
    private int totalUsers;
    private int totalUsersAtivos;

    public Stats(){
        this.ficheiroU = "";
        this.ficheiroB = "";
        this.ficheiroR = "";
        this.wrongReviews = 0;
        this.totalUsersAtivos = 0;
        this.totalUsers = 0;
        this.totalBusinessesAvaliados = 0;
        this.totalBusinesses = 0;
        this.reviewsSemImpacto = 0;
        this.totalReviews = 0;
    }

    public void statsGeral(CatUsers u, CatBusiness b, CatReviews r){
        this.ficheiroU = u.getFicheiro();
        this.ficheiroR = r.getFicheiro();
        this.ficheiroB = b.getFicheiro();
        this.wrongReviews = r.getNumeroReviewsErradas();
        this.totalReviews = r.getNumeroTotalReviews();
        this.totalBusinesses = b.getNumeroTotalBusinesses();
        this.totalUsers = u.getNumeroTotalUsers();
        this.reviewsSemImpacto = r.getReviewsSemImpacto();

        for(Map.Entry<Character, TreeMap<String,Business>> entry_catalogo : b.getCatalogo().entrySet()){
            for(Map.Entry<String,Business> entry_business : b.getCatalogo().get(entry_catalogo.getKey()).entrySet()){
                String business_id = entry_business.getKey();
                if(r.getCatalogo().containsKey(business_id)){
                    this.totalBusinessesAvaliados++;
                }
            }
        }

        for(Map.Entry<Character, TreeMap<String,User>> entry_catalogo : u.getCatalogo().entrySet()){
            for(Map.Entry<String,User> entry_user : u.getCatalogo().get(entry_catalogo.getKey()).entrySet()){
                String user_id = entry_user.getKey();
                if(r.getCatalogo().containsKey(user_id)){
                    this.totalUsersAtivos++;
                }
            }
        }
    }


    public String getFicheiroU() {
        return ficheiroU;
    }

    public void setFicheiroU(String ficheiroU) {
        this.ficheiroU = ficheiroU;
    }

    public String getFicheiroB() {
        return ficheiroB;
    }

    public void setFicheiroB(String ficheiroB) {
        this.ficheiroB = ficheiroB;
    }

    public String getFicheiroR() {
        return ficheiroR;
    }

    public void setFicheiroR(String ficheiroR) {
        this.ficheiroR = ficheiroR;
    }

    public int getWrongReviews() {
        return wrongReviews;
    }

    public void setWrongReviews(int wrongReviews) {
        this.wrongReviews = wrongReviews;
    }

    public int getTotalReviews() {
        return totalReviews;
    }

    public void setTotalReviews(int totalReviews) {
        this.totalReviews = totalReviews;
    }

    public int getReviewsSemImpacto() {
        return reviewsSemImpacto;
    }

    public void setReviewsSemImpacto(int reviewsSemImpacto) {
        this.reviewsSemImpacto = reviewsSemImpacto;
    }

    public int getTotalBusinesses() {
        return totalBusinesses;
    }

    public void setTotalBusinesses(int totalBusinesses) {
        this.totalBusinesses = totalBusinesses;
    }

    public int getTotalBusinessesAvaliados() {
        return totalBusinessesAvaliados;
    }

    public void setTotalBusinessesAvaliados(int totalBusinessesAvaliados) {
        this.totalBusinessesAvaliados = totalBusinessesAvaliados;
    }

    public int getTotalUsers() {
        return totalUsers;
    }

    public void setTotalUsers(int totalUsers) {
        this.totalUsers = totalUsers;
    }

    public int getTotalUsersAtivos() {
        return totalUsersAtivos;
    }

    public void setTotalUsersAtivos(int totalUsersAtivos) {
        this.totalUsersAtivos = totalUsersAtivos;
    }
}
