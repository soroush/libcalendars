package ir.tooska;

import android.os.Build;
import android.support.annotation.RequiresApi;

import java.time.LocalDate;
import java.time.temporal.JulianFields;
import java.util.Date;

public class Calendar {
    public static final int CAL_GREGORIAN        = 0x01;    /* 0b00000001 */
    public static final int CAL_JULIAN           = 0x02;    /* 0b00000010 */
    public static final int CAL_MILANKOVIC       = 0x04;    /* 0b00000100 */
    public static final int CAL_REVISED_JULIAN   = CAL_MILANKOVIC;
    public static final int CAL_ISLAMIC_CIVIL    = 0x08;    /* 0b00001000 */
    public static final int CAL_HIJRI            = CAL_ISLAMIC_CIVIL;
    public static final int CAL_JEWSISH          = 0x10;    /* 0b00010000 */
    public static final int CAL_HEBREW           = CAL_JEWSISH;
    public static final int CAL_SOLAR_HIJRI      = 0x20;    /* 0b00100000 */
    public static final int CAL_SHAMSI           = CAL_SOLAR_HIJRI;
    public static final int CAL_PERSIAN          = CAL_SOLAR_HIJRI;

    private final short year;
    private final short month;
    private final short day;
    private final int type;

    private final int julianDay;

    static {
        System.loadLibrary("calendars");
    }

    private native void from(int type, int jd);
    private native int _to_jdn(int year, int month, int day, int type);

    @RequiresApi(api = Build.VERSION_CODES.O)
    public Calendar(int type)
    {
        Date lDate = new Date();
        java.util.Calendar lCal = java.util.Calendar.getInstance();
        lCal.setTime(lDate);
        int lYear = lCal.get(java.util.Calendar.YEAR);
        int lMonth = lCal.get(java.util.Calendar.MONTH) + 1;
        int lDay = lCal.get(java.util.Calendar.DATE);
        int a = (14 - lMonth) / 12;
        int y = lYear + 4800 - a;
        int m = lMonth + 12 * a - 3;
        julianDay = lDay + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;

        year = 0;
        month = 0;
        day = 0;
        this.type = type;

        from(type, julianDay);
    }

    public Calendar(short year, short month, short day, int type)
    {
        this.year = year;
        this.month = month;
        this.day = day;
        this.type = type;
        julianDay = _to_jdn(year, month, day, type);
    }

    public short getYear() {
        return year;
    }

    public short getMonth() {
        return month;
    }

    public short getDay() {
        return day;
    }

    public String toString() {
        return year + "/" + month + "/" + day;
    }
}
