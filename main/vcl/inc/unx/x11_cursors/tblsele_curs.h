/**************************************************************
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *************************************************************/


#define tblsele_curs_width 16
#define tblsele_curs_height 16
#define tblsele_curs_x_hot 14
#define tblsele_curs_y_hot 8

static const unsigned char tblsele_curs_bits[] = {
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x04,
	0x00,0x0c,
	0x00,0x1c,
	0xfc,0x3f,
	0xfc,0x7f,
	0xfc,0x3f,
	0x00,0x1c,
	0x00,0x0c,
	0x00,0x04,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00};
