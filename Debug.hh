#ifndef DEBUG_HH
# define DEBUG_HH

# include <QDebug>

# define DEBUG(x,y) do { \
  if (y) { qDebug() << x; } \
} while (0)

#endif // DEBUG_HH

