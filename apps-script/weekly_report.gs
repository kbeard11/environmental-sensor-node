function sendWeeklyReport() {

  const sheet = SpreadsheetApp.getActiveSpreadsheet()
    .getSheetByName("Sheet1");

  const data = sheet.getDataRange().getValues();

  if (data.length < 2) {
    return;
  }

  const oneWeekAgo = new Date();
  oneWeekAgo.setDate(oneWeekAgo.getDate() - 7);

  let rows = [];

  for (let i = 1; i < data.length; i++) {

    const timestamp = new Date(data[i][0]);

    if (timestamp >= oneWeekAgo) {
      rows.push(data[i]);
    }
  }

  if (rows.length === 0) {
    return;
  }

  // Moisture
  const moisture1 = rows.map(r => Number(r[6]));
  const moisture2 = rows.map(r => Number(r[7]));

  const avg1 = average(moisture1).toFixed(1);
  const avg2 = average(moisture2).toFixed(1);

  const min1 = Math.min(...moisture1);
  const max1 = Math.max(...moisture1);

  const min2 = Math.min(...moisture2);
  const max2 = Math.max(...moisture2);

  // Temp and humidity
  const air_temp = rows.map(r => Number(r[3]));
  const humidity = rows.map(r => Number(r[4]));

  const avgt = average(air_temp).toFixed(1);
  const avgh = average(humidity).toFixed(1);

  const mint = Math.min(...air_temp);
  const maxt = Math.max(...air_temp);

  const minh = Math.min(...humidity);
  const maxh = Math.max(...humidity);

  const body =
`Weekly Plant and Environmental Report


Environmental:

Average Air Temperature: ${avgt}
Minimum Air Temperature: ${mint}
Maximum Air Temperature: ${maxt}

Average Humidity: ${avgh}
Minimum Humidity: ${minh}
Maximum Humidity: ${maxh}


Plant:

Peperomia:
Average Moisture: ${avg1}
Minimum Moisture: ${max1}
Maximum Moisture: ${min1}

Variegated Peperomia:
Average Moisture: ${avg2}
Minimum Moisture: ${max2}
Maximum Moisture: ${min2}`;

  MailApp.sendEmail(
    "kieranksweetman@gmail.com",
    "Weekly Report",
    body
  );
}

function average(values) {
  return values.reduce((a, b) => a + b, 0) / values.length;
}
